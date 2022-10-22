#include  "../../include/Rays.hpp"

// Constructors Destructors
Rays::Rays(sf::Vector2i mapMaxSize_, int tileSize_, vector<int> mapArray_, float playerAngle_, sf::Vector2f playerPos_)
{
    //Map
    mapMaxSize = mapMaxSize_;
    tileSize = tileSize_;
    mapArray = mapArray_;

    //Player
    playerAngle = playerAngle_;
    playerPos = playerPos_;

    numberOfRays = 360;

    //Colors
    rayColor = sf::Color::Green;
    wallColor = sf::Color(255, 0, 0, 255);

    //Screen
    screenHeight = 700;
    screenWidth = 2.5;
    screenOffsetX = 800;
    screenOffsetY = 250;
}

Rays::~Rays()
{
}

//Private functions
float Rays::calcDistance(float ax, float ay, float bx, float by, float angle)
{
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

//Public functions
void Rays::render(sf::RenderTarget &target, sf::Vector2i mapMaxSize_, int tileSize_, vector<int> mapArray_, float playerAngle_, sf::Vector2f playerPos_)
{
    // Map
    int mapX, mapY, mapPosition, dof = 0;
    mapMaxSize = mapMaxSize_;
    tileSize = tileSize_;
    mapArray = mapArray_;

    //Player
    playerAngle = playerAngle_;
    playerPos = playerPos_;

    // Rays
    int ray = 0;
    float rayX, rayY, rayAngle = 0;
    float xOffset, yOffset = 0;
    float distFinal = 0;

    // Init first ray
    rayAngle = playerAngle - DR * 30;
    if (rayAngle < 0)
        rayAngle += 2 * PI;
    if (rayAngle > 2 * PI)
        rayAngle -= 2 * PI;

    // One loop = 1 ray casting
    for (ray = 0; ray < numberOfRays; ray++)
    {
        // Checking Horizontal Lines
        dof = 0;
        float distHorizontal = 100000;
        float tmpHorizontalRayX = playerPos.x;
        float tmpHorizontalRayY = playerPos.y;

        float aTan = -1 / tan(rayAngle);

        if (rayAngle > PI) // looking up
        {
            // Checking ray first hit position
            rayY = (((int)playerPos.y / tileSize) * tileSize) - 0.0001;
            rayX = (playerPos.y - rayY) * aTan + playerPos.x;

            // Checking ray next hit position
            yOffset = -tileSize;
            xOffset = -yOffset * aTan;
        }

        if (rayAngle < PI) // looking down
        {
            // Checking ray first hit position
            rayY = (((int)playerPos.y / tileSize) * tileSize) + tileSize;
            rayX = (playerPos.y - rayY) * aTan + playerPos.x;

            // Checking ray next hit position
            yOffset = tileSize;
            xOffset = -yOffset * aTan;
        }

        if (rayAngle == 0 || rayAngle == PI) // looking straight left or right
        {
            rayX = playerPos.x;
            rayY = playerPos.y;
            dof = 8;
        }

        while (dof < 8) // Checking where we are in the map array
        {
            mapX = (int)rayX / tileSize;
            mapY = (int)rayY / tileSize;
            mapPosition = mapY * mapMaxSize.x + mapX;

            if (mapPosition > 0 && mapPosition < mapMaxSize.x * mapMaxSize.y && mapArray[mapPosition] > 0) // Hit wall
            {
                // Stocking in tmp to calculate shortest ray between H and V
                tmpHorizontalRayX = rayX;
                tmpHorizontalRayY = rayY;
                distHorizontal = calcDistance(playerPos.x, playerPos.y, tmpHorizontalRayX, tmpHorizontalRayY, playerAngle);
                dof = 8;
            }
            else // Next line
            {
                rayX += xOffset;
                rayY += yOffset;
                dof += 1;
            }
        }

        // -------- Checking Vertical Lines
        dof = 0;
        float distVertical = 100000;
        float tmpVerticalRayX = playerPos.x;
        float tmpVerticalRayY = playerPos.y;

        float nTan = -tan(rayAngle);

        if (rayAngle > P2 && rayAngle < P3) // looking up
        {
            // Checking ray first hit position
            rayX = (((int)playerPos.x / tileSize) * tileSize) - 0.0001;
            rayY = (playerPos.x - rayX) * nTan + playerPos.y;

            // Checking ray next hit position
            xOffset = -tileSize;
            yOffset = -xOffset * nTan;
        }

        if (rayAngle < P2 || rayAngle > P3) // looking down
        {
            // Checking ray first hit position
            rayX = (((int)playerPos.x / tileSize) * tileSize) + tileSize;
            rayY = (playerPos.x - rayX) * nTan + playerPos.y;

            // Checking ray next hit position
            xOffset = tileSize;
            yOffset = -xOffset * nTan;
        }

        if (rayAngle == 0 || rayAngle == PI) // looking straight left or right
        {
            rayX = playerPos.x;
            rayY = playerPos.y;
            dof = 8;
        }

        while (dof < 8) // Checking where we are in the map array
        {
            mapX = (int)rayX / tileSize;
            mapY = (int)rayY / tileSize;
            mapPosition = mapY * mapMaxSize.x + mapX;

            if (mapPosition > 0 && mapPosition < mapMaxSize.x * mapMaxSize.y && mapArray[mapPosition] == 1) // Hit wall
            {
                // Stocking in tmp to calculate shortest ray between H and V
                tmpVerticalRayX = rayX;
                tmpVerticalRayY = rayY;
                distVertical = calcDistance(playerPos.x, playerPos.y, tmpVerticalRayX, tmpVerticalRayY, playerAngle);
                dof = 8;
            }
            else // Next line
            {
                rayX += xOffset;
                rayY += yOffset;
                dof += 1;
            }
        }

        // Checking shortest ray beetween Horizontal and Vertical
        if (distVertical < distHorizontal) //Hiting Vertical Wall
        {
            rayX = tmpVerticalRayX;
            rayY = tmpVerticalRayY;
            distFinal = distVertical;
            wallColor.r = 176;
            rayColor = wallColor;
        }
        if (distHorizontal < distVertical) //Hiting Horizontal Wall
        {
            rayX = tmpHorizontalRayX;
            rayY = tmpHorizontalRayY;
            distFinal = distHorizontal;
            wallColor.r = 255;
            rayColor = wallColor;
        }

        // Drawing rays
        sf::Vertex ray2[2];
        ray2[0] = sf::Vertex(sf::Vector2f(playerPos.x + 4, playerPos.y + 4), rayColor, sf::Vector2f(0, 0));
        ray2[1] = sf::Vertex(sf::Vector2f(rayX, rayY), rayColor, sf::Vector2f(0, 0));
        target.draw(ray2, 2, sf::Lines);

        // Drawing 3D walls
        // Fix fisheye
        float cosineAngle = playerAngle - rayAngle;
        if (cosineAngle < 0)
            cosineAngle += 2 * PI;
        if (cosineAngle > 2 * PI)
            cosineAngle -= 2 * PI;
        distFinal = distFinal * cos(cosineAngle);

        // Line Height
        float lineHeight = (tileSize * screenHeight) / distFinal;
        if (lineHeight > screenHeight)
            lineHeight = screenHeight;

        // Line Offset Up
        float lineOffset = (((screenHeight / 2) - lineHeight) / 2) + screenOffsetY;

        sf::Vertex walls[4];
        walls[0] = sf::Vertex(sf::Vector2f(ray * screenWidth + screenOffsetX, lineOffset), wallColor, sf::Vector2f(0, 0));
        walls[1] = sf::Vertex(sf::Vector2f(ray * screenWidth + screenOffsetX + screenWidth, lineOffset), wallColor, sf::Vector2f(0, 0));
        walls[2] = sf::Vertex(sf::Vector2f(ray * screenWidth + screenOffsetX + screenWidth, lineHeight + lineOffset), wallColor, sf::Vector2f(0, 0));
        walls[3] = sf::Vertex(sf::Vector2f(ray * screenWidth + screenOffsetX, lineHeight + lineOffset), wallColor, sf::Vector2f(0, 0));
        target.draw(walls, 4, sf::Quads);

        // Increasing angle for next ray
        rayAngle += DR / 6;
        if (rayAngle < 0)
            rayAngle += 2 * PI;
        if (rayAngle > 2 * PI)
            rayAngle -= 2 * PI;
    }
}