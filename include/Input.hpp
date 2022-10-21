#include "lib.hpp"

class Input
{
private:
    string typeOfKeyboard;

    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;
    sf::Keyboard::Key upKey;
    sf::Keyboard::Key downKey;
    sf::Keyboard::Key jumpKey;

public:
    Input(string _typeOfKeyboard);
    ~Input();

    const sf::Keyboard::Key &getleftKey() const;
    const sf::Keyboard::Key &getrightKey() const;
    const sf::Keyboard::Key &getupKey() const;
    const sf::Keyboard::Key &getdownKey() const;
    const sf::Keyboard::Key &getjumpKey() const;
};
