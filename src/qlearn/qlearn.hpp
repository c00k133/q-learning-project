#ifndef Q_LEARNING_Q_LEARN
#define Q_LEARNING_Q_LEARN

#include "sfml-drawer.hpp"
#include "physics.hpp"
#include "brain.hpp"

#define QLEARN_DEFAULT_NAME "Q-Learning"
#define QLEARN_DEFAULT_WINDOW_WIDTH 1200
#define QLEARN_DEFAULT_WINDOW_HEIGHT 600
#define QLEARN_DEFAULT_WORM_COLOR sf::Color::Green


namespace QLearnUtils {
    struct WormType {
        int precision;
        unsigned int bone_amount;
        sf::Color color = QLEARN_DEFAULT_WORM_COLOR;
    };
}

class QLearn {
 public:
    explicit QLearn(
            std::string heading = QLEARN_DEFAULT_NAME,
            unsigned int window_width = QLEARN_DEFAULT_WINDOW_WIDTH,
            unsigned int window_height = QLEARN_DEFAULT_WINDOW_HEIGHT);
    ~QLearn();

    void run();

 private:
    inline WormBrain* createWormBrain(
            int precision, unsigned int bone_amount) const;
    WormBrain* createWormType(QLearnUtils::WormType worm_type) const;

    void insertToWorms(unsigned int amount, QLearnUtils::WormType worm_type);

    inline float scaleValue(float value) const;

    void eventHandler();
    void keyPressEventHandler(sf::Keyboard::Key key_press);

    void processWorms();
    void drawComponents();

    sf::RenderWindow* window;
    SFMLDrawer* drawer;
    PhysicsEngine engine;

    WormBrain* master_worm;
    std::vector<WormBrain*> worms;

    std::string heading;  // Title heading of the created SFML window

    float scale = 10.f;
    float camera_offset = 0.f;
    unsigned int window_width;
    unsigned int window_height;

    const sf::Color ground_color = sf::Color::Black;
    const sf::Color clear_color = sf::Color::White;

    static constexpr float window_y_offset = -10.f;
    static constexpr unsigned int framerate_limit = 60;  // FPS in Hertz
};

#endif  // Q_LEARNING_Q_LEARN