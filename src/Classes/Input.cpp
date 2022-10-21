#include "../../include/Input.hpp"

Input::Input(string _typeOfKeyboard) 
{
    typeOfKeyboard = _typeOfKeyboard;

    if (typeOfKeyboard.compare("AZERTY") == 0) {
        leftKey = sf::Keyboard::Key::Q;
        rightKey = sf::Keyboard::Key::D;
        upKey = sf::Keyboard::Key::Z;
        downKey = sf::Keyboard::Key::S;
        jumpKey = sf::Keyboard::Key::Space;
    }
    else if (typeOfKeyboard.compare("QWERTY") == 0) {
        leftKey = sf::Keyboard::Key::A;
        rightKey = sf::Keyboard::Key::D;
        upKey = sf::Keyboard::Key::W;
        downKey = sf::Keyboard::Key::S;
        jumpKey = sf::Keyboard::Key::Space;
    }
    else {
        leftKey = sf::Keyboard::Key::A;
        rightKey = sf::Keyboard::Key::D;
        upKey = sf::Keyboard::Key::W;
        downKey = sf::Keyboard::Key::S;
        jumpKey = sf::Keyboard::Key::Space;
        cout << "Invalid Keyboard" << endl;
    }

}

Input::~Input()
{
    cout << "~Input()" << endl;
}

const sf::Keyboard::Key &Input::getleftKey() const
{
    return leftKey;
}

const sf::Keyboard::Key &Input::getrightKey() const
{
    return rightKey;
}

const sf::Keyboard::Key &Input::getupKey() const
{
    return upKey;
}

const sf::Keyboard::Key &Input::getdownKey() const
{
    return downKey;
}

const sf::Keyboard::Key &Input::getjumpKey() const
{
    return jumpKey;
}