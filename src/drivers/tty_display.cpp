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

void TtyDisplay::drawText(const std::string& text, const uint16_t& x, const uint16_t& y, bool isHighlighted) {
   std::cout << text << std::endl; 
}

void TtyDisplay::drawBox(const uint16_t& width, const uint16_t& height, const bool hasBorder, const bool isFilled, const uint16_t& x, const uint16_t& y) {
    spdlog::debug("draw Box at {} {}", x, y);
} 
