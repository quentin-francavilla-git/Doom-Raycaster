#if !defined(MAP_HPP_)
#define MAP_HPP_

#include "lib.hpp"

class Map {
private:
    sf::Vector2i mapMaxSize;
    int tileSize;
    vector<int> mapArray;

public:
    // Constructors Destructors
    Map(int _size);
    virtual ~Map();

    // Public functions
    void render(sf::RenderTarget &target);

    //Methods
    const int &getTileSizeMap() const;
    const sf::Vector2i &getMapMaxSize() const;
    const vector<int> &getMapArray() const;
};

#endif // MAP_HPP_
