#ifndef SCREEN_H_
#define SCREEN_H_

#include "widget.h"
#include <cstdint>

class Screen
{
private:
    uint8_t m_width;
    uint8_t m_height;
    Widget m_rootWidget; //Make a subclass called RootWidget
public:
    Screen() {}
    Screen(uint8_t width, uint8_t height);
};

#endif // SCREEN_H_
