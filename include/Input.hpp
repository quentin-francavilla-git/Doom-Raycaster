#include "lib.hpp"

class Input
{
private:
    string typeOfKeyboard;
    map<string, sf::Keyboard::Key> inputs_map;

public:
    // Constructors Destructors
    Input(string _typeOfKeyboard);
    virtual ~Input();

    //Methods
    const map<string, sf::Keyboard::Key> &getInputMap() const;
};
