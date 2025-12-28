#include "display.h"
#include <spdlog/spdlog.h>
#include "../ui/screen.h"

Display::Display(bool verticalOrientation)
    : m_verticalOrientation(verticalOrientation) {};

int Display::draw(Screen& screen) {
    spdlog::debug("Attempting to draw on tty display");
    screen.render(this);
    return 0;
}

int Display::redraw() {
    return 1;
};

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
