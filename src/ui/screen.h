#ifndef SCREEN_H_
#define SCREEN_H_

#include "widget.h"
#include <cstdint>

class Screen
{
private:
    const uint8_t m_width;
    const uint8_t m_height;
    Widget m_statusBar; //Make a subclass called statusBarWidget
    Widget rootWidget; //Make a subclass called RootWidget
public:
    Screen();
    Screen(const uint8_t width, const uint8_t height);
};

#endif // SCREEN_H_
