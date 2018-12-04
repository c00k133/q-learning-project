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

}
