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
    speed = 350;
    animState = IDLE;
    characterName = _characterName;
    px = 300;
    py = 300;
}

void Player::initCharacter()
{
}

void Player::initSprite()
{
    playerRectangle = sf::RectangleShape(sf::Vector2f(8, 8));
    playerRectangle.setFillColor(sf::Color(150, 50, 250));
    // set texture
    playerPos.x = 300;
    playerPos.y = 300;
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
    animState = IDLE;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) // Left
    {
        playerRectangle.move(-1.f * dt * speed, 0.f);
        animState = MOVING_LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // Right
    {
        playerRectangle.move(1.f * dt * speed, 0.f);
        animState = MOVING_RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) // UP
    {
        playerRectangle.move(0.f, -1.f * dt * speed);
        animState = MOVING_LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) // Down
    {
        playerRectangle.move(0.f, 1.f * dt * speed);
        animState = MOVING_RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) // Up
    {
    }
}

void Player::updateAnimation()
{
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(playerRectangle);
    target.draw(sprite);
}

const string &Player::getName() const
{
    return name;
}

void Player::setName(string newName)
{
    name.replace(0, newName.length(), newName);
}