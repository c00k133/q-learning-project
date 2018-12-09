#include <tuple>

#include "sfml-drawer.hpp"
#include "body-exceptions.hpp"


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
  const WormBody* worm_body = worm->getBody();

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

 void SFMLDrawer::drawTicks(
        float ground_width,
        unsigned int separation,
        unsigned int text_size) {

  // Load and set font from `.ttl` file
   sf::Font font;
   const std::string font_path =  // String path to `.ttl` file
           "/usr/share/fonts/truetype/roboto/hinted/Roboto-Medium.ttf";
//         "/usr/share/fonts/TTF/DejaVuSerif.ttf";
   // FIXME(Cookie): create utility class, possibly with config file
   if (!font.loadFromFile(font_path)) {
     throw QLearningExceptions::BodyRuntimeException(
             "Font path [" + font_path + "] was not found");
   }

   // Styling of ticks
   sf::Text ticks;
   ticks.setFont(font);
   ticks.setCharacterSize(text_size);
   ticks.setFillColor(sf::Color::White);

   // Draw tick numbers on ground at `separation` intervals
   for (unsigned int i = 0; i < ground_width / separation; ++i) {
     const int tick_number = i * separation;
     // Draw negative tick marks
     ticks.setString(std::to_string(-tick_number));
     ticks.setPosition(sf::Vector2f(-tick_number * scale, 100.f));
     window->draw(ticks);
     // Draw positive tick marks
     ticks.setString(std::to_string(tick_number));
     ticks.setPosition(sf::Vector2f(tick_number * scale, 100.f));
     window->draw(ticks);
   }
}

