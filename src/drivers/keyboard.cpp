#include "keyboard.h"

#include <iostream>

Keyboard::Keyboard() {}

Keyboard::~Keyboard() {}

char Keyboard::read() {
    char c;
    std::cin >> c;
    return c;
}

void Keyboard::cleanUp() {}

