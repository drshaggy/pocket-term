#include "tty_display.h"

TtyDisplay::TtyDisplay() :
    Display()
{};

int TtyDisplay::initialise() {
    std::clog << "TtyDisplay Initialised" << std::endl;
    return 0;
}
