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
    mapX = 8;
    mapY = 8;
    mapS = 64;

    map = {
        1,1,1,1,1,1,1,1,
        1,0,1,0,0,0,0,1,
        1,0,1,0,0,0,0,1,
        1,0,1,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,1,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,
    };
}

void Game::initWindow()
{
    videoMode.height = WINDOW_HEIGHT;
    videoMode.width = WINDOW_WIDTH;
    videoMode.bitsPerPixel = 32;
    window = new sf::RenderWindow(videoMode, "Doom", sf::Style::Fullscreen);
    window->setFramerateLimit(144);
}

void Game::initPlayer()
{
    player = (Player **) malloc(MAX_PLAYERS * sizeof(Player));
    player[0] = new Player("Pablo", "Jotaro");
}

// Public Functions
void Game::renderMap2D()
{
    int x, y, xo, yo = 0;
    sf::Color mapColor = sf::Color::White;
    sf::Vertex vertices[4];

    for (y = 0; y < mapY; y++) {
        for (x = 0; x < mapX; x++) {
            if (map[y * mapX + x] == 1)
                mapColor = sf::Color::White;
            else
                mapColor = sf::Color::Black;

            xo = x * mapS;
            yo = y * mapS;
            
            vertices[0] = sf::Vertex(sf::Vector2f(xo + 1, yo + 1), mapColor, sf::Vector2f(0,  0));
            vertices[1] = sf::Vertex(sf::Vector2f(xo + 1, yo + mapS - 1), mapColor, sf::Vector2f(0,  10));
            vertices[2] = sf::Vertex(sf::Vector2f(xo + mapS - 1, yo + mapS - 1), mapColor, sf::Vector2f(10,  10));
            vertices[3] = sf::Vertex(sf::Vector2f(xo + mapS - 1, yo + 1), mapColor, sf::Vector2f(10,  0));

            window->draw(vertices, 4, sf::Quads);
        }
    }
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

    window->display();
}

void Game::updateMousePositions()
{
    mousePosWindows = sf::Mouse::getPosition(*window);
}


//Player Functions
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