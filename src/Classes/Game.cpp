#include "../../include/Game.hpp"

// Constructors / Destructors
Game::Game()
{
    initVariables();
    initWindow();
    initPlayer();
    initMap();
    initRays();
}

Game::~Game()
{
    delete window;
    // free(player);
    // delete player;
}

// Private Functions
void Game::initVariables()
{
    window = nullptr;
    dt = 0;
}

void Game::initMap()
{
    map = unique_ptr<Map>(new Map(64));
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
    //player = (Player **)malloc(MAX_PLAYERS * sizeof(Player));
    //player[0] = new Player("Pablo", "Jotaro");
    // unique_ptr<Player> player_ptr[0] = new Player("Pablo", "Jotaro");
    player.push_back(unique_ptr<Player>(new Player("Pablo", "Jotaro")));
}

void Game::initRays()
{
    rays = unique_ptr<Rays>(new Rays(map->getMapMaxSize(), map->getTileSizeMap(),
    map->getMapArray(), player[0]->getPlayerAngle(), player[0]->getPlayerPosition()));
}

// Public Functions
void Game::renderMap2D()
{
    map->render(*window);
}

void Game::renderRays()
{
    rays->render(*window, map->getMapMaxSize(), map->getTileSizeMap(),
    map->getMapArray(), player[0]->getPlayerAngle(), player[0]->getPlayerPosition());
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
    player[0]->update(dt, map->getTileSizeMap(), map->getMapArray(), map->getMapMaxSize());
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