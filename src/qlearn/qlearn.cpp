#include "qlearn.hpp"


QLearn::QLearn(
      std::string heading,
      unsigned int window_width,
      unsigned int window_height) :
      heading(heading),
      window_width(window_width),
      window_height(window_height) {

  window = new sf::RenderWindow(
          sf::VideoMode(window_width, window_height), heading);
  window->setFramerateLimit(framerate_limit);

  // Set companion object
  drawer = new SFMLDrawer(window);
  drawer->setScale(scale);

  // Set master worm, used for centering camera.
  master_worm = createWormBrain(20, 4);
  worms.push_back(master_worm);

  view = sf::View(
      sf::Vector2f(0, 0), sf::Vector2f(window_width, window_height));
}

QLearn::~QLearn() {
  // Deleter each worm
  for (auto worm : worms) {
    delete worm;
  }
}

inline WormBrain* QLearn::createWormBrain(
        int precision, unsigned int bone_amount) const {
  return new WormBrain(engine.getWorld(), precision, bone_amount);
}

WormBrain* QLearn::createWormType(QLearnUtils::WormType worm_type) const {
  WormBrain* worm = createWormBrain(worm_type.precision, worm_type.bone_amount);
  worm->setBodyColor(worm_type.color);
  return worm;
}

void QLearn::insertToWorms(
        unsigned int amount, QLearnUtils::WormType worm_type) {
  for (unsigned int i = 0; i < amount; ++i) {
     WormBrain* worm = createWormType(worm_type);
     worms.push_back(worm);
  }
}

inline float QLearn::scaleValue(float value) const {
  return value * scale;
}

void QLearn::keyPressEventHandler(sf::Keyboard::Key key_press) {
  switch (key_press) {
    case sf::Keyboard::Right: case sf::Keyboard::Left:
      if (follow_master) {
        follow_master = false;
        const float current_master_x =
            master_worm->getBodyCoordinatesVector().x;
        camera_offset = scaleValue(current_master_x);
      }
      camera_offset += key_press == sf::Keyboard::Right ?
          QLEARN_CAMERA_OFFSET_INCREMENT : -QLEARN_CAMERA_OFFSET_INCREMENT;
      break;

    case sf::Keyboard::Space:
      camera_offset = 0.f;
      follow_master = true;
      break;

    default:
      break;
  }
}

void QLearn::eventHandler() {
  sf::Event event;
  while (window->pollEvent(event)) {
    switch (event.type) {  // TODO(Cookie): fill out with other key-presses
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
  // We process each worm with dynamic parallelism
  // One process might take longer than others depending on precision
  #pragma omp parallel for schedule(dynamic, 1)
  for (auto worm = worms.begin(); worm < worms.end(); ++worm) {
    (*worm)->process();
  }
}

void QLearn::drawComponents() {
  // Drawing of worms happen sequentially, drawing in parallel breaks SFML
  for (auto worm : worms) {
    drawer->drawWorm(worm);
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
  const float y_dimension = view.getSize().y / 2 - 53 * scale;
  auto information_position =
      view.getCenter() - sf::Vector2f(x_dimension, y_dimension);
  drawer->drawWormInformation(master_worm, information_position);
}

void QLearn::setViewCenter() {
  float x_view;
  if (follow_master) {
    auto master_coordinates = master_worm->getBodyCoordinatesVector();
    x_view = scaleValue(master_coordinates.x);
  } else {
    x_view = camera_offset;
  }

  float y_view = scaleValue(window_y_offset);
  view.setCenter(x_view, y_view);
}

void QLearn::run() {
  while (window->isOpen()) {
    // Fix view according to the master worm
    setViewCenter();
    window->setView(view);

    engine.step();
    window->clear(clear_color);

    // Check all events that might have happened
    eventHandler();
    // Process each worm independently
    processWorms();
    // Draw all components on window
    drawComponents();

    window->display();
  }
}
