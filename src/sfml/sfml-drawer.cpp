#include <tuple>

#include "sfml-drawer.hpp"


namespace SFMLDrawer {

    void drawGround(
            sf::RenderWindow &window,
            b2Body *ground_body,
            b2Vec2 ground_dimensions,
            sf::Color color) {

      float ground_width = ground_dimensions.x;
      float ground_height = ground_dimensions.y;

      b2Fixture *fixture = ground_body->GetFixtureList();
      while (fixture) {
        sf::RectangleShape ground(sf::Vector2f(ground_width, ground_height));

        ground.setFillColor(color);
        ground.setOrigin(ground_width / 2.f, ground_height / 2.f);

        const b2Vec2 ground_position = ground_body->GetPosition();
        ground.setPosition(ground_position.x, ground_position.y);
        ground.setRotation(ground_body->GetAngle() * 180 / b2_pi);
        window.draw(ground);

        fixture = fixture->GetNext();
      }
    }

    void drawWorm(sf::RenderWindow &window, WormBrain* worm) {
      std::tuple<float, float> bone_dimensions = worm->getBodyBoneDimensions();
      float bone_width = std::get<0>(bone_dimensions);
      float bone_length = std::get<1>(bone_dimensions);

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
            bone_shape.setPosition(bone_position.x, bone_position.y);

            bone_shape.setRotation(bone->GetAngle() * 180 / b2_pi);
            bone_shape.setOutlineThickness(1.f);
            bone_shape.setOutlineColor(sf::Color::Black);

            window.draw(bone_shape);
          }

          fixture = fixture->GetNext();
        }
      }
    }

}
