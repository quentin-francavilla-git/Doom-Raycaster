#if !defined(GAME_HPP_)
#define GAME_HPP_

#include "lib.hpp"
#include "Player.hpp"

#define WINDOW_WIDTH 1980
#define WINDOW_HEIGHT 1080
#define MAX_PLAYERS 1

class Game
{
private:
    // Variables
    // Window
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    // Time
    sf::Clock clock;
    float dt;

    // Mouse
    sf::Vector2i mousePosWindows;

    // Objects
    Player **player;

    // Map
    int mapX;
    int mapY;
    int mapS;
    std::vector<int> map;

    // Private Functions
    void initVariables();
    void initWindow();
    void initPlayer();
    void initMap();

public:
    // Constructors / Destructors
    Game();
    virtual ~Game();

    // Public Functions
    // Core Functions
    const bool running() const;
    void pollEvents();
    void update();
    void updateTime();
    float getTime();
    void render();
    void updateMousePositions();

    // Player
    void updatePlayer();
    void renderPlayer();
    Player getPlayer(int indexPlayer);

    // Map
    void renderMap2D();
};

#endif // GAME_HPP_
