#include "display.h"
#include <spdlog/spdlog.h>
#include "../ui/screen.h"
#include "../ui/status_bar.h"

Display::Display(bool verticalOrientation)
    : m_verticalOrientation(verticalOrientation) {};

int Display::draw(Screen& screen) {
    spdlog::debug("Attempting to draw screen on display");
    clear();
    screen.render(this);
    return 0;
}

int Display::draw(StatusBar& statusBar) {
    spdlog::debug("Attempting to draw status bar on display");
    //clear();
    statusBar.render(this);
    return 0;
}

int Display::clear() {
    return 1;
};

int Display::print([[maybe_unused]]const std::string& text) {
    return 1;
}

int Display::printHighlighted([[maybe_unused]]const std::string& text) {
    return 1;
}

int Display::println([[maybe_unused]]const std::string& text) {
    return 1;
}
