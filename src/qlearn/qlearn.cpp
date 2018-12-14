#include "qlearn.hpp"


void QLearn::init() {
  sf::VideoMode video_mode(window_width, window_height);
  window = std::make_shared<sf::RenderWindow>(video_mode, heading);
  window->setFramerateLimit(framerate_limit);

  // Set companion object
  drawer = std::unique_ptr<SFMLDrawer>(new SFMLDrawer(window));
  drawer->setScale(scale);

  // Set master worm, used for centering camera.
  worms.push_back(std::shared_ptr<WormBrain>(createWormBrain(20, 4, "Master")));

  view = sf::View(
      sf::Vector2f(0, 0), sf::Vector2f(window_width, window_height));
}

QLearn::QLearn(
      std::string heading,
      unsigned int window_width,
      unsigned int window_height) :
      heading(heading),
      window_width(window_width),
      window_height(window_height) {
  init();
}

QLearn::QLearn(unsigned int amount,
               int precision,
               unsigned int bone_amount,
               std::string heading,
               unsigned int window_width,
               unsigned int window_height) :
               heading(heading),
               window_width(window_width),
               window_height(window_height) {
  init();

  // Create extra worms
  QLearnUtils::WormType worm_type = {
      precision,
      bone_amount,
      QLEARN_DEFAULT_WORM_COLOR,
      WORMBRAIN_DEFAULT_NAME
  };
  insertToWorms(amount, worm_type);
}

inline WormBrain* QLearn::createWormBrain(
        int precision, unsigned int bone_amount, std::string name) const {
  return new WormBrain(
          engine.getWorld(),
          precision,
          bone_amount,
          WORMBRAIN_DEFAULT_MAX_ERROR,
          name);
}

WormBrain* QLearn::createWormType(
    const QLearnUtils::WormType& worm_type) const {
  WormBrain* worm = createWormBrain(
          worm_type.precision, worm_type.bone_amount, worm_type.name);
  worm->setBodyColor(worm_type.color);
  return worm;
}

inline std::shared_ptr<WormBrain> QLearn::getMasterWorm() const {
  return worms[master_worm_index];
}

void QLearn::insertToWorms(
        unsigned int amount, QLearnUtils::WormType worm_type) {
  std::string original_name = worm_type.name;
  for (unsigned int i = 0; i < amount; ++i) {
    worm_type.name = original_name + std::to_string(i + 1);
    WormBrain* worm = createWormType(worm_type);
    worms.push_back(std::shared_ptr<WormBrain>(worm));
  }
}

inline float QLearn::scaleValue(float value) const {
  return value * scale;
}

void QLearn::printHelp() const {
  std::ifstream file_stream(help_file_path);
  if (file_stream.rdstate() & (file_stream.failbit | file_stream.badbit)) {
    std::cerr << "Failed to load help file!" << std::endl;
  } else {
    while (!file_stream.eof()) {
      std::string line;
      std::getline(file_stream, line);
      std::cout << line << std::endl;
    }
  }
}

void QLearn::keyPressEventHandler(sf::Keyboard::Key key_press) {
  switch (key_press) {
    case sf::Keyboard::Right: case sf::Keyboard::Left:
      if (follow_master) {
        follow_master = false;
        const float current_master_x =
            getMasterWorm()->getBodyCoordinatesVector().x;
        camera_offset = scaleValue(current_master_x);
      }
      camera_offset += key_press == sf::Keyboard::Right ?
          QLEARN_CAMERA_OFFSET_INCREMENT : -QLEARN_CAMERA_OFFSET_INCREMENT;
      break;

    case sf::Keyboard::Add: case sf::Keyboard::Subtract: {
      const float increment = 1.f + (key_press == sf::Keyboard::Add ?
          -QLEARN_CAMERA_ZOOM_INCREMENT : QLEARN_CAMERA_ZOOM_INCREMENT);
      view.zoom(increment);
      zoom_value *= increment;
      break;
    }

    case sf::Keyboard::Space:
      // Fix camera to original values
      camera_offset = 0.f;
      follow_master = true;

      // Reset the zoom value of the view
      view.zoom(1.f / zoom_value);
      zoom_value = 1.f;

      // Reset engine time step
      engine.resetTimeStep();

      // Reset master worm variables
      getMasterWorm()->getBody()->resetMaxMotorTorque();
      getMasterWorm()->getBody()->resetMotorSpeed();
      getMasterWorm()->resetQLearningMoveReward();
      break;

    case sf::Keyboard::Escape:
      window->close();
      break;

    case sf::Keyboard::H:
      printHelp();
      break;

    case sf::Keyboard::M: case sf::Keyboard::N:
      if (key_press == sf::Keyboard::M)
        master_worm_index =
            (master_worm_index + 1) % (unsigned int) worms.size();
      else
        master_worm_index = master_worm_index - 1 < 0 ?
            static_cast<int>(worms.size()) - 1 : master_worm_index - 1;
      break;

    case sf::Keyboard::R: {
      const bool random_act = getMasterWorm()->getRandomAct();
      // Invert randomness of master worm
      getMasterWorm()->setRandomActs(!random_act);
      break;
    }

    case sf::Keyboard::P:
      run_physics = !run_physics;
      break;

    case sf::Keyboard::A: case sf::Keyboard::S: {
      const float32 change = key_press == sf::Keyboard::A ? -1.f : 1.f;
      engine.alterTimeStep(change);
      break;
    }

    case sf::Keyboard::Q: {
      const bool original_run_physics = run_physics;
      run_physics = true;
      for (unsigned int i = 0; i < 1000; ++i) {
        advanceWorld();
      }
      run_physics = original_run_physics;
      break;
    }

    case sf::Keyboard::Z: case sf::Keyboard::X: {
      const float change = key_press == sf::Keyboard::Z ? 1000.f : -1000.f;
      getMasterWorm()->getBody()->alterMaxMotorTorque(change);
      break;
    }

    case sf::Keyboard::C: case sf::Keyboard::V: {
      const float change = key_press == sf::Keyboard::C ? -0.1f : 0.1f;
      getMasterWorm()->getBody()->alterMotorSpeed(change);
      break;
    }

    case sf::Keyboard::W: case sf::Keyboard::E: {
      const float change = key_press == sf::Keyboard::W ? 0.05f : -0.05f;
      getMasterWorm()->alterQLearningMoveReward(change);
      break;
    }

    default:
      break;
  }
}

void QLearn::eventHandler() {
  sf::Event event;
  while (window->pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        window->close();
        break;

      case sf::Event::KeyPressed:
        keyPressEventHandler(event.key.code);
        break;

      default:
        break;
    }
  }
}

void QLearn::processWorms() {
  // One process might take longer than others depending on precision
  for (auto worm = worms.begin(); worm < worms.end(); ++worm) {
    (*worm)->process();
  }

  // NOTE: we attempted to use parallelism here through openmp, but
  //       unfortunately it introduced valgrind errors "possibly lost".
  //       This might have been a false positive, but we are staying on the
  //       on the safe side and ignoring parallelism for now.
}

void QLearn::drawComponents() {
  // Drawing of worms happen sequentially, drawing in parallel breaks SFML
  for (const auto& worm : worms) {
    drawer->drawWorm(*worm);
  }

  // Draw the ground based on PhysicsEngine
  const b2Vec2 ground_dimensions = engine.getGroundDimensions();
  drawer->drawGround(
          engine.getGround(), ground_dimensions, ground_color);

  // Draw ticks on ground
  drawer->drawTicks(ground_dimensions.x);

  // Draw information about the current master worm
  // TODO(Cookie): find a better way to calculate these
  const float x_dimension = view.getSize().x / 2 - 3 * scale;
  const float y_dimension = view.getSize().y / 2 - 3 * scale;
  auto information_position =
      view.getCenter() - sf::Vector2f(x_dimension, y_dimension);
  drawer->drawWormInformation(*getMasterWorm(), information_position);
}

void QLearn::setViewCenter() {
  float x_view;
  if (follow_master) {
    auto master_coordinates = getMasterWorm()->getBodyCoordinatesVector();
    x_view = scaleValue(master_coordinates.x);
  } else {
    x_view = camera_offset;
  }

  float y_view = scaleValue(window_y_offset);
  view.setCenter(x_view, y_view);
}

inline void QLearn::advanceWorld() {
  if (run_physics) {
    engine.step();
    processWorms();
  }
}

void QLearn::run() {
  printHelp();

  while (window->isOpen()) {
    // Fix view according to the master worm
    setViewCenter();
    window->setView(view);

    window->clear(clear_color);

    // Advance forward in the world: step the PhysicsEngine and process worms
    advanceWorld();

    // Check all events that might have happened
    eventHandler();
    // Draw all components on window
    drawComponents();

    window->display();
  }
}
