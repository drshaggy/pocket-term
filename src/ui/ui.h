#ifndef UI_H_
#define UI_H_

#include "../drivers/display.h"

#include <string>
#include <memory>

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
    void update();
};

#endif // UI_H_
