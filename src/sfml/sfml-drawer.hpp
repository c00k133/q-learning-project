#ifndef Q_LEARNING_SFML_DRAWER_HPP
#define Q_LEARNING_SFML_DRAWER_HPP

#include <fstream>
#include <iomanip>
#include <sstream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Box2D/Box2D.h"
#include "brain.hpp"

#define SFML_DRAWER_DEFAULT_GROUND_COLOR sf::Color::Black
#define SFML_DRAWER_DEFAULT_SEPARATION 10
#define SFML_DRAWER_DEFAULT_TEXT_SIZE 24
#define SFML_DRAWER_DEFAULT_TICK_Y_POSITION 80.f


/** Companion class for QLearn objects. */
class SFMLDrawer {
public:
    /**
     * Constructor for SFMLDrawer.
     * Draws chosen methods on input window.
     */
    explicit SFMLDrawer(sf::RenderWindow *window);

    /**
     * Setter for scale used in scaling drawings on `window`.
     * @param new_scale new scale to use
     */
    void setScale(float new_scale);

    /**
     * Draw input ground onto `window`, x and y dimensions separately.
     * @param ground_body input body to draw
     * @param ground_x_dimension "height" of the ground
     * @param ground_y_dimension "length" of the ground
     * @param color color for ground, defaults to
     *              SFML_DRAWER_DEFAULT_GROUND_COLOR
     */
    void drawGround(b2Body& ground_body,
                    float ground_x_dimension,
                    float ground_y_dimension,
                    sf::Color color = SFML_DRAWER_DEFAULT_GROUND_COLOR);

    /**
     * Draw input ground onto `window`, dimensions as b2Vec2.
     * @param ground_body input body to draw
     * @param ground_dimensions dimensions of ground
     * @param color color for ground, defaults to
     *              SFML_DRAWER_DEFAULT_GROUND_COLOR
     */
    void drawGround(
            b2Body& ground_body,
            b2Vec2 ground_dimensions,
            sf::Color color = SFML_DRAWER_DEFAULT_GROUND_COLOR);

    /**
     * Draw one worm at a time.
     * @param worm input worm to be drawn
     */
    void drawWorm(WormBrain* worm);

    /**
     * Draw ground ticks for distance measurement.
     * @param ground_width width of whole ground
     * @param separation separation of ticks, defaults to
     *                   SFML_DRAWER_DEFAULT_SEPARATION
     * @param text_size text size of tick numbers, defaults to
     *                  SFML_DRAWER_DEFAULT_TEXT_SIZE
     */
    void drawTicks(
            float ground_width,
            unsigned int separation = SFML_DRAWER_DEFAULT_SEPARATION,
            unsigned int text_size = SFML_DRAWER_DEFAULT_TEXT_SIZE,
            float tick_y_position = SFML_DRAWER_DEFAULT_TICK_Y_POSITION);

    /**
     * Draw information about a specific worm onto the SFML window.
     * @param worm worm to get information from
     * @param position position of information as a sf::Vector2f
     */
    void drawWormInformation(
        WormBrain* worm,
        sf::Vector2f position,
        unsigned int text_size = SFML_DRAWER_DEFAULT_TEXT_SIZE);

private:
    // TODO(Cookie): move this to a utility library
    /**
     * Helper method for checking if file exists.
     * Source:
     *  https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
     * @param file_path path to file
     * @return true if file exists, false otherwise
     */
    inline bool checkFileExistence(const std::string &file_path) const;

    /* Helper method for extracting font files. */
    sf::Font getFont() const;

    // Font to be used for all text
    sf::Font font;

    // Window onto which everything is drawn
    sf::RenderWindow *window;
    // Scaling of objects on window
    float scale = 1.f;

    // Paths to different fonts
    const std::vector<std::string> font_paths = {
            // Copied to build by CMake
            "./assets/Roboto-Medium.ttf",

            // System specific default fallback font
            // FIXME(Cookie): we should not rely on system specifics, this
            //                hard-coded solution should not be our only
            //                solution, maybe a config file?
            "/usr/share/fonts/truetype/roboto/hinted/Roboto-Medium.ttf",

            // Another system specific default
            "/usr/share/fonts/TTF/DejaVuSans.ttf"
    };

    // Color used drawing ticks
    sf::Color text_color = sf::Color::White;
};

#endif  // Q_LEARNING_SFML_DRAWER_HPP
