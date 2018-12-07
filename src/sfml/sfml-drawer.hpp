#ifndef Q_LEARNING_SFML_DRAWER_HPP
#define Q_LEARNING_SFML_DRAWER_HPP

#include <SFML/Graphics.hpp>

#include "Box2D/Box2D.h"
#include "brain.hpp"

namespace SFMLDrawer {

    void drawGround(
            sf::RenderWindow &window,
            b2Body* ground_body,
            b2Vec2 ground_dimensions,
            float scale,
            sf::Color color = sf::Color::Black);
            // TODO(Cookie): localize color to world

    void drawWorm(sf::RenderWindow &window, WormBrain* worm, float scale);

    void drawTicks(
            sf::RenderWindow &window,
            float scale,
            float ground_width,
            int separation = 10,
            unsigned int text_size = 24);

}

#endif  // Q_LEARNING_SFML_DRAWER_HPP