#include <tuple>

#include "sfml-drawer.hpp"
#include "body-exceptions.hpp"


SFMLDrawer::SFMLDrawer(sf::RenderWindow* window) : window(window) {
  font = getFont();
}

void SFMLDrawer::setScale(float new_scale) {
  scale = new_scale;
}

void SFMLDrawer::drawGround(
        b2Body* ground_body,
        float ground_x_dimension,
        float ground_y_dimension,
        sf::Color color) {

  // Get and scale ground dimensions
  float ground_width = ground_x_dimension * scale;
  float ground_height = (ground_y_dimension + 10) * scale;
  // FIXME(Cookie): localize calculations of ground dimensions
  //float ground_height = ground_y_dimension * scale;

  // Get fixture list head
  b2Fixture *fixture = ground_body->GetFixtureList();

  // Loop through list until list end
  while (fixture) {
    // Create shape for ground
    sf::RectangleShape ground(sf::Vector2f(ground_width, ground_height));
    // Set desired color
    ground.setFillColor(color);
    // Set origin to the middle point of the shape
    ground.setOrigin(ground_width / 2.f, ground_height / 2.f);
    // FIXME(Cookie): check if ground needs to be rotated
    //ground.setRotation(ground_body->GetAngle() * 180 / b2_pi);

    // Get, scale, and set ground position
    const b2Vec2 ground_position = ground_body->GetPosition();
    const float32 x_position = ground_position.x * scale;
    const float32 y_position = ground_position.y * scale;
    ground.setPosition(x_position, y_position);

    // Finally draw the ground
    window->draw(ground);

    // Get the next fixture in list
    fixture = fixture->GetNext();
  }
}

void SFMLDrawer::drawGround(
        b2Body *ground_body,
        b2Vec2 ground_dimensions,
        sf::Color color) {

  // Explode b2Vec2 `ground_dimensions`
  drawGround(
          ground_body, ground_dimensions.x, ground_dimensions.y, color);
}

 void SFMLDrawer::drawWorm(WormBrain* worm) {
  // Get WormBody object out of `worm`
  const std::shared_ptr<WormBody> worm_body = worm->getBody();

  // Get shape of bones from `worm`, used in loop below
  std::tuple<float, float> bone_dimensions = worm_body->getBoneDimensions();
  float bone_width = std::get<0>(bone_dimensions) * scale;
  float bone_length = std::get<1>(bone_dimensions) * scale;

  std::vector<b2Body *> bones = worm_body->getBones();
  for (auto bone : bones) {
    // Get head of fixture list
    b2Fixture *fixture = bone->GetFixtureList();

    // Loop while list contains fixture objects
    while (fixture) {
      if (fixture->GetType() == b2Shape::e_polygon) {
        // Draw the bone shapes with dimensions from `worm`
        sf::RectangleShape
                bone_shape(sf::Vector2f(bone_width, bone_length));

        // Get and set color from `worm`
        sf::Color body_color = worm_body->getBodyColor();
        bone_shape.setFillColor(body_color);

        // Set initial position based on the shape of `worm`
        bone_shape.setOrigin(bone_width / 2.f, bone_length / 2.f);

        // Get position of each bone from `bone`
        const b2Vec2 bone_position = bone->GetPosition();
        const float32 x_position = bone_position.x * scale;
        const float32 y_position = bone_position.y * scale;
        bone_shape.setPosition(x_position, y_position);
        bone_shape.setRotation(bone->GetAngle() * 180 / b2_pi);

        // Fix outlines around bones
        bone_shape.setOutlineThickness(1.f);
        sf::Color body_outline_color = worm_body->getBodyOutlineColor();
        bone_shape.setOutlineColor(body_outline_color);

        // Finally draw the whole worm
        window->draw(bone_shape);
      }
      // Get next fixture
      fixture = fixture->GetNext();
    }
  }
}

inline bool SFMLDrawer::checkFileExistence(
         const std::string &file_path) const {
  if (FILE* file = fopen(file_path.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

sf::Font SFMLDrawer::getFont() const {
  sf::Font font;

  // Try to find a font file
  for (const std::string& fonts : font_paths) {
    if (checkFileExistence(fonts)) {
      if (!font.loadFromFile(fonts)) {
        throw QLearningExceptions::BodyRuntimeException(
                "Could not load font file: " + fonts);
      }
      return font;
    }
  }

  // Return empty font object
  return font;
}

void SFMLDrawer::drawTicks(
        float ground_width,
        unsigned int separation,
        unsigned int text_size,
        float tick_y_position) {

   // Styling of ticks
   sf::Text ticks;
   ticks.setFont(font);
   ticks.setCharacterSize(text_size);
   ticks.setColor(text_color);

   // Draw tick numbers on ground at `separation` intervals
   for (unsigned int i = 0; i < ground_width / separation; ++i) {
     const int tick_number = i * separation;
     // Draw negative tick marks
     ticks.setString(std::to_string(-tick_number));
     ticks.setPosition(sf::Vector2f(-tick_number * scale, tick_y_position));
     window->draw(ticks);
     // Draw positive tick marks
     ticks.setString(std::to_string(tick_number));
     ticks.setPosition(sf::Vector2f(tick_number * scale, tick_y_position));
     window->draw(ticks);
   }
}

void SFMLDrawer::drawWormInformation(
    WormBrain *worm, sf::Vector2f position, unsigned int text_size) {
  sf::Text information;
  information.setFont(font);
  information.setCharacterSize(text_size);
  information.setColor(text_color);

  // Set string indicator if worm is acting randomly or not
  std::string random_act = worm->getRandomAct() ? "(R)" : "(O)";

  // String stream for string formatting
  std::stringstream worm_information;

  worm_information << worm->getName() << random_act << " - ";
  worm_information << "iterations: " << worm->getCount();
  worm_information << "\nx position: ";
  const float worm_x_position = worm->getBodyCoordinatesVector().x;
  worm_information << std::fixed << std::setprecision(2) << worm_x_position;

  information.setString(worm_information.str());
  information.setPosition(position);

  window->draw(information);
}
