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
    //Data
    name = _name;
    speed = 20;
    animState = IDLE;
    characterName = _characterName;


    //Positions
    playerPos.x = 310;
    playerPos.y = 313;
    playerPosInMap.x = playerPos.x / tileSize;
    playerPosInMap.y = playerPos.y / tileSize;
    playerMoveOffset.x = 0;
    playerMoveOffset.y = 0;

    //Collisions
    CollisionOffset.x = 0;
    CollisionOffset.y = 0;
    playerPosInMap_add_Offset.x = 0;
    playerPosInMap_add_Offset.y = 0;
    playerPosInMap_sub_Offset.x = 0;
    playerPosInMap_sub_Offset.y = 0;


    //Angle
    playerDelta.x = cos(playerAngle) * 5;
    playerDelta.y = sin(playerAngle) * 5;
    playerAngle = 0;

    inputs = shared_ptr<Input> (new Input("AZERTY"));
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
void Player::update(float dt, int tileSize_, vector<int> mapArray_, sf::Vector2i mapMaxSize_)
{
    mapMaxSize = mapMaxSize_;
    tileSize = tileSize_;
    mapArray = mapArray_;
    updateMovement(dt);
    updateAnimation();
    updateCollisions(dt);
}

void Player::updateCollisions(float dt)
{
    playerPosInMap.x = playerPos.x / tileSize;
    playerPosInMap.y = playerPos.y / tileSize;

    if (playerDelta.x < 0)
        CollisionOffset.x = - 20;
    else
        CollisionOffset.x = 20;

    if (playerDelta.y < 0)
        CollisionOffset.y = - 20;
    else
        CollisionOffset.y = 20;

    playerPosInMap_add_Offset.x = (playerPos.x + CollisionOffset.x) / 64.0;
    playerPosInMap_add_Offset.y = (playerPos.y + CollisionOffset.y) / 64.0;
    playerPosInMap_sub_Offset.x = (playerPos.x - CollisionOffset.x) / 64.0;
    playerPosInMap_sub_Offset.y = (playerPos.y - CollisionOffset.y) / 64.0;
}

void Player::updatePhysics()
{
}

void Player::updateMovement(float dt)
{
    if (sf::Keyboard::isKeyPressed(inputs->getInputMap().at("leftKey"))) // Left
    {
        playerAngle -= 6 * dt;

        if (playerAngle < 0)
            playerAngle += 2 * PI;
        
        playerDelta.x = cos(playerAngle) * 5;
        playerDelta.y = sin(playerAngle) * 5;
    }
    else if (sf::Keyboard::isKeyPressed(inputs->getInputMap().at("rightKey"))) // Right
    {
        playerAngle += 6 * dt;

        if (playerAngle > 2 * PI)
            playerAngle -= 2 * PI;
        
        playerDelta.x = cos(playerAngle) * 5;
        playerDelta.y = sin(playerAngle) * 5;
    }
    if (sf::Keyboard::isKeyPressed(inputs->getInputMap().at("upKey"))) // UP
    {
        if (mapArray[playerPosInMap.y * mapMaxSize.x + playerPosInMap_add_Offset.x] == 0) {
            playerMoveOffset.x = playerDelta.x * speed * dt;
        }
        else
            playerMoveOffset.x = 0;

        if (mapArray[playerPosInMap_add_Offset.y * mapMaxSize.x + playerPosInMap.x] == 0) {
            playerMoveOffset.y = playerDelta.y * speed * dt;
        }
        else
            playerMoveOffset.y = 0;

        playerRectangle.move(playerMoveOffset.x, playerMoveOffset.y);
    }
    else if (sf::Keyboard::isKeyPressed(inputs->getInputMap().at("downKey"))) // Down
    {
        if (mapArray[playerPosInMap.y * mapMaxSize.x + playerPosInMap_sub_Offset.x] == 0) {
            playerMoveOffset.x = -playerDelta.x * speed * dt;
        }
        else
            playerMoveOffset.x = 0;

        if (mapArray[playerPosInMap_sub_Offset.y * mapMaxSize.x + playerPosInMap.x] == 0) {
            playerMoveOffset.y = -playerDelta.y * speed * dt;
        }
        else
            playerMoveOffset.y = 0;
        playerRectangle.move(playerMoveOffset.x, playerMoveOffset.y);
    }
    if (sf::Keyboard::isKeyPressed(inputs->getInputMap().at("jumpKey"))) // Up
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


    // //draw direction line
    // sf::Vertex lineVertices[1];

    // lineVertices[0] = sf::Vertex(sf::Vector2f(playerPos.x + 4, playerPos.y + 4), sf::Color::Red, sf::Vector2f(0, 0));
    // lineVertices[1] = sf::Vertex(sf::Vector2f(playerPos.x + 4 + playerDelta.x * 5, playerPos.y + 4 + playerDelta.y * 5),
    // sf::Color::Red, sf::Vector2f(0, 10));

    // target.draw(lineVertices, 2, sf::Lines);
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