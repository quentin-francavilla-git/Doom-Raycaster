#include "../../include/Map.hpp"

// Constructors Destructors
Map::Map(int _tileSize)
{
    mapMaxSize.x = 8;
    mapMaxSize.y = 8;
    tileSize = _tileSize;

    mapArray = {
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

Map::~Map()
{
}

void Map::render(sf::RenderTarget &target)
{
    int x, y = 0;
    int xOffset, yOffset = 0;
    sf::Color mapColor = sf::Color::White;
    sf::Vertex vertices[3];

    for (y = 0; y < mapMaxSize.y; y++)
    {
        for (x = 0; x < mapMaxSize.x; x++)
        {
            if (mapArray[y * mapMaxSize.x + x] == 1)
                mapColor = sf::Color::White;
            else
                mapColor = sf::Color::Black;

            xOffset = x * tileSize;
            yOffset = y * tileSize;

            vertices[0] = sf::Vertex(sf::Vector2f(xOffset + 1, yOffset + 1), mapColor, sf::Vector2f(0, 0));
            vertices[1] = sf::Vertex(sf::Vector2f(xOffset + 1, yOffset + tileSize - 1), mapColor, sf::Vector2f(0, 10));
            vertices[2] = sf::Vertex(sf::Vector2f(xOffset + tileSize - 1, yOffset + tileSize - 1), mapColor, sf::Vector2f(10, 10));
            vertices[3] = sf::Vertex(sf::Vector2f(xOffset + tileSize - 1, yOffset + 1), mapColor, sf::Vector2f(10, 0));

            target.draw(vertices, 4, sf::Quads);
        }
    }
}

const int &Map::getTileSizeMap() const
{
    return tileSize;
}

const sf::Vector2i &Map::getMapMaxSize() const
{
    return mapMaxSize;
}

const vector<int> &Map::getMapArray() const
{
    return mapArray;
}