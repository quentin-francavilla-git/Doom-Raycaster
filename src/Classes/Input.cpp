#include "../../include/Input.hpp"

Input::Input(string _typeOfKeyboard) 
{
        typeOfKeyboard = _typeOfKeyboard;

    if (typeOfKeyboard.compare("AZERTY") == 0) {
        inputs_map["leftKey"] = sf::Keyboard::Key::Q;
        inputs_map["rightKey"] = sf::Keyboard::Key::D;
        inputs_map["upKey"] = sf::Keyboard::Key::Z;
        inputs_map["downKey"] = sf::Keyboard::Key::S;
        inputs_map["jumpKey"] = sf::Keyboard::Key::Space;
    }
    else if (typeOfKeyboard.compare("QWERTY") == 0) {
        inputs_map["leftKey"] = sf::Keyboard::Key::A;
        inputs_map["rightKey"] = sf::Keyboard::Key::D;
        inputs_map["upKey"] = sf::Keyboard::Key::W;
        inputs_map["downKey"] = sf::Keyboard::Key::S;
        inputs_map["jumpKey"] = sf::Keyboard::Key::Space;
    }
    else {
        inputs_map["leftKey"] = sf::Keyboard::Key::A;
        inputs_map["rightKey"] = sf::Keyboard::Key::D;
        inputs_map["upKey"] = sf::Keyboard::Key::W;
        inputs_map["downKey"] = sf::Keyboard::Key::S;
        inputs_map["jumpKey"] = sf::Keyboard::Key::Space;
        cout << "Invalid Keyboard" << endl;
    }

}

Input::~Input()
{
}

const map<string, sf::Keyboard::Key> &Input::getInputMap() const
{
    return inputs_map;
}