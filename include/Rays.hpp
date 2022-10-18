#if !defined(RAYS_HPP_)
#define RAYS_HPP_

#include "lib.hpp"

class Rays
{
private:
    int numberOfRays;
    sf::Color rayColor;
    sf::Color wallColor;

    //Screen
    int screenWidth;
    int screenHeight;
    int screenOffsetX;
    int screenOffsetY;

    //Map
    sf::Vector2i mapMaxSize;
    int tileSize;
    vector<int> mapArray;

    //Player
    float playerAngle;
    sf::Vector2f playerPos;

    //Private Functions
    float calcDistance(float ax, float ay, float bx, float by, float angle);

public:
    // Constructors Destructors
    Rays(sf::Vector2i mapMaxSize_, int tileSize_, vector<int> mapArray_, float playerAngle_, sf::Vector2f playerPos_);
    virtual ~Rays();

    void render(sf::RenderTarget &target, sf::Vector2i mapMaxSize_, int tileSize_, vector<int> mapArray_, float playerAngle_, sf::Vector2f playerPos_);
};

#endif // RAYS_HPP_
