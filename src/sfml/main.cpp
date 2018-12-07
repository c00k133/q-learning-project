#include <SFML/Graphics.hpp>

#include "brain.hpp"
#include "physics.hpp"
#include "Box2D/Box2D.h"
#include "sfml-drawer.hpp"


int main() {
  const float scale = 10.f;
  const float window_y_offset = -10.f;
  const unsigned int window_width = 1200;
  const unsigned int window_height = 600;

  float camera_offset = 0.f;

  sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window_width, window_height));
  sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Testing");
  window.setFramerateLimit(60);

  PhysicsEngine engine = PhysicsEngine();
  b2World* world = engine.getWorld();
  auto worm = new WormBrain(world, 20, 4);

  while (window.isOpen()) {
    auto body_coordinates = worm->getBodyCoordinatesVector();
    view.setCenter(
        body_coordinates.x * scale + camera_offset, window_y_offset * scale);
    window.setView(view);

    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {  // TODO(Cookie): fill out with other key-presses
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
           switch (event.key.code) {
             case sf::Keyboard::Right:
               camera_offset += 5.f;
               break;
             case sf::Keyboard::Left:
               camera_offset -= 5.f;
               break;
             case sf::Keyboard::Space:
               camera_offset = 0.f;
               break;
             default:
               break;
           }
          break;

        default:
          break;
      }
    }

    engine.step();
    window.clear(sf::Color::White);
    worm->process();

    const b2Vec2 ground_dimensions = engine.getGroundDimensions();
    SFMLDrawer::drawGround(
            window, engine.getGround(), ground_dimensions, scale);
    SFMLDrawer::drawWorm(window, worm, scale);
    SFMLDrawer::drawTicks(window, scale, ground_dimensions.x);

    window.display();
    std::cout << "round: " << worm->getCount() << std::endl;
  }

  delete worm;

  return 0;
}
