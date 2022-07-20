#include "../../include/Player.hpp"

// Constructors Destructors
Player::Player(string _name, string _characterName)
{
    initVariables(_name, _characterName);
    initCharacter();
    initSprite();
    initAnimation();
}

Player::~Player()
{
}

// Private Functions
void Player::initVariables(string _name, string _characterName)
{
    name = _name;
    speed = 20;
    animState = IDLE;
    characterName = _characterName;

    playerPos.x = 300;
    playerPos.y = 300;
    playerDelta.x = cos(playerAngle) * 5;
    playerDelta.y = sin(playerAngle) * 5;
    playerAngle = 0;
}

void Player::initCharacter()
{
}

void Player::initSprite()
{
    playerRectangle = sf::RectangleShape(sf::Vector2f(8, 8));
    playerRectangle.setFillColor(sf::Color(150, 50, 250));
    playerRectangle.setPosition(playerPos);
}

void Player::initAnimation()
{
    animationTimer.restart();
}

// Public Functions
void Player::update(float dt)
{
    updateMovement(dt);
    updateAnimation();
}

void Player::updatePhysics()
{
}

void Player::updateMovement(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) // Left
    {
        playerAngle -= 6 * dt;

        if (playerAngle < 0)
            playerAngle += 2 * PI;
        
        playerDelta.x = cos(playerAngle) * 5;
        playerDelta.y = sin(playerAngle) * 5;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // Right
    {
        playerAngle += 6 * dt;

        if (playerAngle > 2 * PI)
            playerAngle -= 2 * PI;
        
        playerDelta.x = cos(playerAngle) * 5;
        playerDelta.y = sin(playerAngle) * 5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) // UP
    {
        playerRectangle.move(playerDelta.x * speed * dt, playerDelta.y * speed * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) // Down
    {
        playerRectangle.move(-playerDelta.x, -playerDelta.y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) // Up
    {
    }
    playerPos = playerRectangle.getPosition();
}

void Player::updateAnimation()
{
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(playerRectangle);
    target.draw(sprite);


    //draw direction line
    sf::Vertex lineVertices[1];

    lineVertices[0] = sf::Vertex(sf::Vector2f(playerPos.x + 4, playerPos.y + 4), sf::Color::Red, sf::Vector2f(0, 0));
    lineVertices[1] = sf::Vertex(sf::Vector2f(playerPos.x + 4 + playerDelta.x * 5, playerPos.y + 4 + playerDelta.y * 5),
    sf::Color::Red, sf::Vector2f(0, 10));

    target.draw(lineVertices, 2, sf::Lines);
}

const string &Player::getName() const
{
    return name;
}

const float &Player::getPlayerAngle() const
{
    return playerAngle;
}
const sf::Vector2f &Player::getPlayerPosition() const
{
    return playerPos;
}

void Player::setName(string newName)
{
    name.replace(0, newName.length(), newName);
}