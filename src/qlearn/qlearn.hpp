#ifndef Q_LEARNING_Q_LEARN
#define Q_LEARNING_Q_LEARN

#include "sfml-drawer.hpp"
#include "physics.hpp"
#include "brain.hpp"

#define QLEARN_DEFAULT_NAME "Q-Learning"
#define QLEARN_DEFAULT_WINDOW_WIDTH 1200
#define QLEARN_DEFAULT_WINDOW_HEIGHT 600
#define QLEARN_DEFAULT_WORM_COLOR sf::Color::Green
#define QLEARN_CAMERA_OFFSET_INCREMENT 5.f
#define QLEARN_CAMERA_ZOOM_INCREMENT 0.05f


namespace QLearnUtils {
    /**
     * WormType structure contains flavors of different WormBrains.
     * The structure contains information for a WormBrain initialization, such
     * as precision of QLearning object, amount of bones in WormBody, and the
     * bone color for a WormBody object.
     */
    struct WormType {
        int precision;
        unsigned int bone_amount;
        sf::Color color;
        std::string name;
    };
}


class QLearn {
 public:
    /**
     * QLearn constructor, takes care of the window dimensions and name.
     * @param heading name/title of SFML window
     * @param window_width width of SFML window
     * @param window_height height of SFML window
     */
    explicit QLearn(
            std::string heading = QLEARN_DEFAULT_NAME,
            unsigned int window_width = QLEARN_DEFAULT_WINDOW_WIDTH,
            unsigned int window_height = QLEARN_DEFAULT_WINDOW_HEIGHT);

    /**
     * QLearn constructor that creates multiple worms to the world.
     * @param amount amount of extra worms
     * @param precision precision of extra worms
     * @param bone_amount amount of bones in extra worms
     * @param heading name/title of SFML window
     * @param window_width width of SFML window
     * @param window_height height of SFML window
     */
    QLearn(
        unsigned int amount,
        int precision,
        unsigned int bone_amount,
        std::string heading = QLEARN_DEFAULT_NAME,
        unsigned int window_width = QLEARN_DEFAULT_WINDOW_WIDTH,
        unsigned int window_height = QLEARN_DEFAULT_WINDOW_HEIGHT);

    /**
     * QLearn destructor, takes care of deleting all allocate memory.
     * E.g. all WormBrain objects.
     */
    ~QLearn();

    /** Run and loop the whole program. */
    void run();

 private:
    /** Common initialization method for constructors. */
    void init();

    /**
     * Helper method for creating WormBrain objects within the current world.
     * @param precision precision of QLearning object for this WormBrain
     * @param bone_amount amount of bones in companion WormBody object
     * @return pointer to newly created WormBrain
     */
    inline WormBrain* createWormBrain(
            int precision,
            unsigned int bone_amount,
            std::string name = WORMBRAIN_DEFAULT_NAME) const;

    /**
     * Create a WormBrain of specific WormType flavor.
     * @param worm_type the flavor fo the WormBrain
     * @return pointer to newly created WormBrain flavor
     */
    WormBrain* createWormType(QLearnUtils::WormType& worm_type) const;

    /**
     * Insert a certain amount of WormBrains with `worm_type` flavor to vector
     * `worms`.
     * @param amount amount of WormBrains to be created
     * @param worm_type flavor of this specific WormBrain
     */
    void insertToWorms(unsigned int amount, QLearnUtils::WormType worm_type);

    /**
     * Helper method for scaling values when drawing.
     * @param value value to be scaled
     * @return scaled value
     */
    inline float scaleValue(float value) const;

    /** Event handler for SFML window input. */
    void eventHandler();

    /**
     * Helper method for handling specific key presses within the SFML window.
     * @param key_press the current key press
     */
    void keyPressEventHandler(sf::Keyboard::Key key_press);

    /** Process each worm separately. */
    void processWorms();

    /**
     * Draw each component onto the SFML window.
     * Utilizes the companion SFMLDrawer object.
     */
    void drawComponents();

    /** Helper method for setting the center of the view. */
    void setViewCenter();

    /** Method for printing help to std::cout. */
    void printHelp() const;

    sf::RenderWindow* window;  // SFML window where the action happens
    sf::View view;  // View used in addition to window

    SFMLDrawer* drawer;  // Companion SFMLDrawer object
    PhysicsEngine engine;  // The physics engine for this specific instance

    int master_worm_index = 0;  // Index of master worm in `worms`
    WormBrain* master_worm;  // Master worm which the SFML view defaults to
    std::vector<WormBrain*> worms;  // All saved worm instances

    std::string heading;  // Title heading of the created SFML window

    bool follow_master = true;  // Should the view follow the master worm?
    float camera_offset = 0.f;  // X offset of camera in SFML window

    float zoom_value = 1.f;
    float scale = 10.f;  // Scaling of drawings on the SFML window
    unsigned int window_width;  // SFML window width
    unsigned int window_height;  // SFML window height

    const sf::Color ground_color = sf::Color::Black;  // Color of ground
    // Color that clear the SFML window
    const sf::Color clear_color = sf::Color::White;

    // Constant y offset of the SFML window
    static constexpr float window_y_offset = -10.f;
    static constexpr unsigned int framerate_limit = 60;  // FPS in Hertz

    // Path to help file
    // TODO(Cookie): put this in a config file
    const std::string help_file_path = "./assets/help.txt";
};

#endif  // Q_LEARNING_Q_LEARN