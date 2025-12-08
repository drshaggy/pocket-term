#ifndef UI_H_
#define UI_H_

#include <string>
#include "drivers/display.h"

class UI
{
private:
    Display& m_display;
public:
    UI();
    UI(Display& display) : m_display(display) {};
    void print(const std::string& text);
    void println(const std::string& text);
    void clear();
};

#endif // UI_H_
