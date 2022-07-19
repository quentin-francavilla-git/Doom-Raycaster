#if !defined(PLAYER_HPP_)
#define PLAYER_HPP_

#include "lib.hpp"

enum PLAYER_ANIMATION_STATES
{
    IDLE = 0,
    MOVING_LEFT,
    MOVING_RIGHT,
    JUMPING,
    FALLING
};

class Player
{
private:
    //Globals
    sf::Sprite sprite;
    string characterName;
    string name;
    float speed;
    sf::Clock animationTimer;
    sf::Texture texture;
    sf::RectangleShape playerRectangle;

    //Position
    sf::Vector2f playerDelta;
    sf::Vector2f playerPos;
    float playerAngle;

    // Animation
    short animState;
    sf::IntRect *currentFrame;

    // Physics
    sf::Vector2f velocity;
    float acceleration;
    float deceleration;

    // Private Functions
    void initVariables(string _name, string _characterName);
    void initCharacter();
    void initSprite();
    void initAnimation();

public:
    // Constructors Destructors
    Player(string _name, string _characterName);
    virtual ~Player();

    // Public Functions
    void updatePhysics();
    void updateMovement(float dt);
    void updateAnimation();
    void update(float dt);
    void render(sf::RenderTarget &target);

    const string &getName() const;
    void setName(string newName);
};

#endif // PLAYER_HPP_
