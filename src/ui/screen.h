#ifndef SCREEN_H_
#define SCREEN_H_

#include "widget.h"
#include <cstdint>
#include <memory>

class Display;

class Screen
{
private:
    uint16_t m_width;
    uint16_t m_height;
    std::unique_ptr<Widget> m_rootWidget; //Make a subclass called RootWidget
public:
    Screen() = default;
    Screen(uint16_t width, uint16_t height);
    Screen(const Screen& other);
    Screen& operator=(const Screen& other);
    void setRootWidget(std::unique_ptr<Widget> widget) {m_rootWidget = std::move(widget);}
    std::unique_ptr<Widget>& getRootWidget() {return m_rootWidget;}
    void render(Display* display);
};

#endif // SCREEN_H_
