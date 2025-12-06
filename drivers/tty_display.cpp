#include "tty_display.h"

TtyDisplay::TtyDisplay() :
    Display()
{};

int TtyDisplay::initialise() {
    std::clog << "TtyDisplay Initialised" << std::endl;
    return 0;
}

int TtyDisplay::clear() {
    std::cout << "\033[2J\033[H";
    return 0;
}
