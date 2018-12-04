#ifndef Q_LEARNING_SFML_DRAWER_HPP
#define Q_LEARNING_SFML_DRAWER_HPP

#include <SFML/Graphics.hpp>

#include "Box2D/Box2D.h"

namespace SFMLDrawer {

    void drawGround(
            sf::RenderWindow &window,
            b2Body *ground_body,
            b2Vec2 ground_dimensions,
            sf::Color color = sf::Color::Cyan);

}

#endif  // Q_LEARNING_SFML_DRAWER_HPP