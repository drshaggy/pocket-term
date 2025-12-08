#include "tty_display.h"

TtyDisplay::TtyDisplay() :
    Display()
{};

int TtyDisplay::initialise() {
    std::this_thread::sleep_for(500ms);
    std::clog << "TtyDisplay Initialised" << std::endl;
    return 0;
}

int TtyDisplay::clear() {
    std::this_thread::sleep_for(500ms);

    std::cout << "\033[2J\033[H" << std::flush;
    return 0;
}

int TtyDisplay::print(const std::string& text) {
    std::this_thread::sleep_for(500ms);
    std::cout << text << std::flush;
    return 0;
}

int TtyDisplay::printHighlighted(const std::string& text) {
    std::this_thread::sleep_for(500ms);
    std::cout << "\033[7m" + text + "\033[0m" << std::flush;
    return 0;
}

int TtyDisplay::println(const std::string& text) {
    std::this_thread::sleep_for(500ms);
    std::cout << text << std::endl;
    return 0;
}
