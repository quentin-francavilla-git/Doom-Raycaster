#include "../../include/Game.hpp"

// Constructors / Destructors
Game::Game()
{
    initVariables();
    initWindow();
    initPlayer();
    initMap();
}

Game::~Game()
{
    delete window;
    free(player);
    delete player;
}

// Private Functions
void Game::initVariables()
{
    window = nullptr;
    dt = 0;
}

void Game::initMap()
{
    map = new Map(64);
}

void Game::initWindow()
{
    videoMode.height = WINDOW_HEIGHT;
    videoMode.width = WINDOW_WIDTH;
    videoMode.bitsPerPixel = 32;
    window = new sf::RenderWindow(videoMode, "Doom", sf::Style::Close);
    window->setFramerateLimit(144);
}

void Game::initPlayer()
{
    player = (Player **)malloc(MAX_PLAYERS * sizeof(Player));
    player[0] = new Player("Pablo", "Jotaro");
}

// Public Functions
float Game::calcDistance(float ax, float ay, float bx, float by, float angle)
{
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void Game::renderRays()
{
    // Map
    sf::Vector2i mapMaxSize = map->getMapMaxSize();
    int mapX, mapY, mapPosition, dof = 0;
    int tileSize = map->getTileSizeMap();
    std::vector<int> mapArray = map->getMapArray();
    sf::Color wallColor(255, 0, 0, 255);

    // Rays
    int ray = 0;
    float rayX, rayY, rayAngle = 0;
    float xOffset, yOffset = 0;
    float distFinal = 0;
    sf::Color rayColor = sf::Color::Green;

    // Player
    float playerAngle = player[0]->getPlayerAngle();
    sf::Vector2f playerPos = player[0]->getPlayerPosition();

    // Init first ray
    rayAngle = playerAngle - DR * 30;
    if (rayAngle < 0)
        rayAngle += 2 * PI;
    if (rayAngle > 2 * PI)
        rayAngle -= 2 * PI;

    // One loop = 1 ray casting
    for (ray = 0; ray < 60; ray++)
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
            rayY = (((int)playerPos.y / 64) * 64) - 0.0001;
            rayX = (playerPos.y - rayY) * aTan + playerPos.x;

            // Checking ray next hit position
            yOffset = -tileSize;
            xOffset = -yOffset * aTan;
        }

        if (rayAngle < PI) // looking down
        {
            // Checking ray first hit position
            rayY = (((int)playerPos.y / 64) * 64) + tileSize;
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
            mapX = (int)rayX / 64;
            mapY = (int)rayY / 64;
            mapPosition = mapY * mapMaxSize.x + mapX;

            if (mapPosition > 0 && mapPosition < mapMaxSize.x * mapMaxSize.y && mapArray[mapPosition] == 1) // Hit wall
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
            rayX = (((int)playerPos.x / 64) * 64) - 0.0001;
            rayY = (playerPos.x - rayX) * nTan + playerPos.y;

            // Checking ray next hit position
            xOffset = -tileSize;
            yOffset = -xOffset * nTan;
        }

        if (rayAngle < P2 || rayAngle > P3) // looking down
        {
            // Checking ray first hit position
            rayX = (((int)playerPos.x / 64) * 64) + tileSize;
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
            mapX = (int)rayX / 64;
            mapY = (int)rayY / 64;
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
        }
        if (distHorizontal < distVertical) //Hiting Horizontal Wall
        {
            rayX = tmpHorizontalRayX;
            rayY = tmpHorizontalRayY;
            distFinal = distHorizontal;
            wallColor.r = 255;
        }

        // Drawing rays
        sf::Vertex ray2[2];
        ray2[0] = sf::Vertex(sf::Vector2f(playerPos.x + 4, playerPos.y + 4), rayColor, sf::Vector2f(0, 0));
        ray2[1] = sf::Vertex(sf::Vector2f(rayX, rayY), rayColor, sf::Vector2f(0, 0));
        window->draw(ray2, 2, sf::Lines);

        // Drawing 3D walls
        // Fix fisheye
        float cosineAngle = playerAngle - rayAngle;
        if (cosineAngle < 0)
            cosineAngle += 2 * PI;
        if (cosineAngle > 2 * PI)
            cosineAngle -= 2 * PI;
        distFinal = distFinal * cos(cosineAngle);

        // Line Height
        float lineHeight = (tileSize * 320) / distFinal;
        if (lineHeight > 320)
            lineHeight = 320;

        // Line Offset
        float lineOffset = (160 - lineHeight) / 2;

        sf::Vertex walls[4];
        walls[0] = sf::Vertex(sf::Vector2f(ray * 8 + 530, lineOffset), wallColor, sf::Vector2f(0, 0));
        walls[1] = sf::Vertex(sf::Vector2f(ray * 8 + 530 + 20, lineOffset), wallColor, sf::Vector2f(0, 0));
        walls[2] = sf::Vertex(sf::Vector2f(ray * 8 + 530 + 20, lineHeight + lineOffset), wallColor, sf::Vector2f(0, 0));
        walls[3] = sf::Vertex(sf::Vector2f(ray * 8 + 530, lineHeight + lineOffset), wallColor, sf::Vector2f(0, 0));
        window->draw(walls, 4, sf::Quads);

        // Increasing angle for next ray
        rayAngle += DR;
        if (rayAngle < 0)
            rayAngle += 2 * PI;
        if (rayAngle > 2 * PI)
            rayAngle -= 2 * PI;
    }
}

void Game::renderMap2D()
{
    map->render(*window);
}

const bool Game::running() const
{
    return window->isOpen();
}

void Game::pollEvents()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        }
    }
}

void Game::updateTime()
{
    dt = clock.restart().asSeconds();
}

float Game::getTime()
{
    return dt;
}

void Game::update()
{
    pollEvents();
    updateMousePositions();
    updatePlayer();
    updateTime();
}

void Game::render()
{
    window->clear(sf::Color(45, 45, 45, 255));

    // draw
    renderMap2D();
    renderPlayer();
    renderRays();

    window->display();
}

void Game::updateMousePositions()
{
    mousePosWindows = sf::Mouse::getPosition(*window);
}

// Player Functions
void Game::updatePlayer()
{
    player[0]->update(dt);
}

void Game::renderPlayer()
{
    player[0]->render(*window);
}

Player Game::getPlayer(int indexPlayer)
{
    if (indexPlayer <= MAX_PLAYERS)
        return *player[indexPlayer];
    else
        return *player[0];
}