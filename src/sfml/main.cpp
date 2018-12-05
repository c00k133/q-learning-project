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
  auto worm = new WormBrain(24, world);

  while (window.isOpen()) {
    auto xyy = worm->getBodyCoordinatesVector();
    view.setCenter(xyy.x, -10);
    window.setView(view);

    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {  // TODO(Cookie): fill out with other key-presses
        case sf::Event::Closed:
          window.close();
          break;

        default:
          break;
      }
    }

    engine.step();
    window.clear(sf::Color::White);

    SFMLDrawer::drawGround(
            window, engine.getGround(), engine.getGroundDimensions());
    SFMLDrawer::drawWorm(window, worm);

    worm->process();
    window.display();
  }

  delete worm;

  return 0;
}
