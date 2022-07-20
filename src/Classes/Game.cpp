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
void Game::renderRays()
{
    // Map
    sf::Vector2i mapMaxSize = map->getMapMaxSize();
    int mapX, mapY, mapPosition, dof = 0;
    int tileSize = map->getTileSizeMap();
    std::vector<int> mapArray = map->getMapArray();

    // Rays
    int ray = 0;
    float rayX, rayY, rayAngle = 0;
    float xOffset, yOffset = 0;

    // Player
    float playerAngle = player[0]->getPlayerAngle();
    sf::Vector2f playerPos = player[0]->getPlayerPosition();

    rayAngle = playerAngle;

    for (ray = 0; ray < 1; ray++)
    {
        //Checking Horizontal Lines
        dof = 0;

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
                dof = 8;
            }
            else // Next line
            {
                rayX += xOffset;
                rayY += yOffset;
                dof += 1;
            }
        }
        sf::Vertex ray[2];

        ray[0] = sf::Vertex(sf::Vector2f(playerPos.x + 4, playerPos.y + 4), sf::Color::Red, sf::Vector2f(0, 0));
        ray[1] = sf::Vertex(sf::Vector2f(rayX + 4, rayY + 4), sf::Color::Red, sf::Vector2f(0, 10));
        window->draw(ray, 2, sf::Lines);

        // Checking Vertical Lines
        dof = 0;

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
                dof = 8;
            }
            else // Next line
            {
                rayX += xOffset;
                rayY += yOffset;
                dof += 1;
            }
        }
        sf::Vertex ray2[4];

        ray2[0] = sf::Vertex(sf::Vector2f(playerPos.x, playerPos.y), sf::Color::Green, sf::Vector2f(0, 0));
        ray2[1] = sf::Vertex(sf::Vector2f(playerPos.x + 8, playerPos.y + 8), sf::Color::Green, sf::Vector2f(0, 0));
        ray2[2] = sf::Vertex(sf::Vector2f(rayX + 8, rayY + 8), sf::Color::Green, sf::Vector2f(0, 0));
        ray2[3] = sf::Vertex(sf::Vector2f(rayX, rayY), sf::Color::Green, sf::Vector2f(0, 10));
        window->draw(ray2, 4, sf::Quads);
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