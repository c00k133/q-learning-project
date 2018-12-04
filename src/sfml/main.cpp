#include <SFML/Graphics.hpp>

#include "brain.hpp"
#include "physics.hpp"
#include "Box2D/Box2D.h"
#include "sfml-drawer.hpp"


int main() {
  sf::View view(sf::Vector2f(0, 0), sf::Vector2f(300, 300));
  sf::RenderWindow window(sf::VideoMode(300, 300), "Testing");
  window.setFramerateLimit(60);

  PhysicsEngine engine = PhysicsEngine();
  b2World* world = engine.getWorld();
  WormBrain* worm = new WormBrain(24, world);

  while (window.isOpen()) {
    auto xyy = worm->getBodyCoordinatesVector();
    view.setCenter(xyy.x, -10);
    window.setView(view);

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    world->Step(1.f / 60.f, 8, 3);

    window.clear(sf::Color::White);

    SFMLDrawer::drawGround(
            window, engine.getGround(), engine.getGroundDimensions());

    std::vector<b2Body*> bones = worm->getBodyBones();
    for (auto bone : bones) {
      for (b2Fixture* fixture = bone->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
        if (fixture->GetType() == b2Shape::e_polygon) {
          sf::RectangleShape w(sf::Vector2f(10, 10));
          w.setFillColor(sf::Color(88, 222, 255));
          w.setOrigin(10 / 2, 10 / 2);
          w.setPosition(bone->GetPosition().x, bone->GetPosition().y);
          w.setRotation(bone->GetAngle() * 180 / b2_pi);
          w.setOutlineThickness(1.f);
          w.setOutlineColor(sf::Color::Black);
          window.draw(w);
        }
      }
    }

    worm->process();

    window.display();
  }

  delete worm;

  return 0;
}
