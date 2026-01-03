#include "tty_display.h"
#include "../ui/screen.h"

#include <spdlog/spdlog.h>
#include <iostream>
#include <thread>


using namespace std::chrono_literals;

TtyDisplay::TtyDisplay(bool verticalOrientation) :
    Display(verticalOrientation)
{
    m_ready = true;
    spdlog::info("TtyDisplay Initialised");
};

int TtyDisplay::clear() {
    std::this_thread::sleep_for(500ms);

    std::cout << "\033[2J\033[H" << std::flush;
    return 0;
}

void TtyDisplay::drawText(const std::string& text, const uint8_t& x, const uint8_t& y) {
   std::cout << text << std::endl; 
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

