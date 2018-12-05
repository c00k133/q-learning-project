#include <tuple>

#include "sfml-drawer.hpp"
#include "body-exceptions.hpp"


namespace SFMLDrawer {

    void drawGround(
            sf::RenderWindow &window,
            b2Body *ground_body,
            b2Vec2 ground_dimensions,
            float scale,
            sf::Color color) {

      float ground_width = ground_dimensions.x * scale;
      //float ground_height = ground_dimensions.y * scale;
      float ground_height = (ground_dimensions.y + 10) * scale;

      b2Fixture *fixture = ground_body->GetFixtureList();
      while (fixture) {
        sf::RectangleShape ground(sf::Vector2f(ground_width, ground_height));

        ground.setFillColor(color);
        ground.setOrigin(ground_width / 2.f, ground_height / 2.f);
        //ground.setRotation(ground_body->GetAngle() * 180 / b2_pi);

        const b2Vec2 ground_position = ground_body->GetPosition();
        const float32 x_position = ground_position.x * scale;
        const float32 y_position = ground_position.y * scale;
        ground.setPosition(x_position, y_position);

        window.draw(ground);
        fixture = fixture->GetNext();
      }
    }

    void drawWorm(sf::RenderWindow &window, WormBrain* worm, float scale) {
      std::tuple<float, float> bone_dimensions = worm->getBodyBoneDimensions();
      float bone_width = std::get<0>(bone_dimensions) * scale;
      float bone_length = std::get<1>(bone_dimensions) * scale;

      std::vector<b2Body*> bones = worm->getBodyBones();
      for (auto bone : bones) {
        b2Fixture* fixture = bone->GetFixtureList();
        while (fixture) {
          if (fixture->GetType() == b2Shape::e_polygon) {
            sf::RectangleShape
                bone_shape(sf::Vector2f(bone_width, bone_length));

            // TODO(Cookie): localize colors to the worm body
            bone_shape.setFillColor(sf::Color(88, 222, 255));
            bone_shape.setOrigin(bone_width / 2.f, bone_length / 2.f);

            const b2Vec2 bone_position = bone->GetPosition();
            const float32 x_position = bone_position.x * scale;
            const float32 y_position = bone_position.y * scale;
            bone_shape.setPosition(x_position, y_position);

            //bone_shape.setRotation(bone->GetAngle() * 180 / b2_pi);
            bone_shape.setOutlineThickness(1.f);
            bone_shape.setOutlineColor(sf::Color::Black);

            window.draw(bone_shape);
          }

          fixture = fixture->GetNext();
        }
      }
    }

    void drawTicks(
            sf::RenderWindow &window,
            float scale,
            float ground_width,
            int separation,
            unsigned int text_size) {

      sf::Font font;
      const std::string font_path =
            "/usr/share/fonts/truetype/roboto/hinted/Roboto-Medium.ttf";

      if (!font.loadFromFile(font_path)) {
        throw QLearningExceptions::BodyRuntimeException(
                "Font path ["
                + font_path
                + "] was not found");
      }

      sf::Text ticks;
      ticks.setFont(font);
      ticks.setCharacterSize(text_size);
      ticks.setFillColor(sf::Color::White);

      for (unsigned int i = 0; i < ground_width / separation; ++i) {
        ticks.setString(std::to_string(i * separation));
        ticks.setPosition(sf::Vector2f(i * separation * scale, 100.f));
        window.draw(ticks);
      }
    }

}
