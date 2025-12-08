#ifndef UI_H_
#define UI_H_

#include <string>
#include "drivers/display.h"
#include "drivers/tty_display.h"

class UI
{
private:
    std::unique_ptr<Display> m_display;
public:
    UI();
    void print(const std::string& text);
    void printHighlighted(const std::string& text);
    void println(const std::string& text);
    void clear();
};

#endif // UI_H_
