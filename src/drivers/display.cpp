#include "display.h"

Display::Display(bool verticalOrientation)
    : m_verticalOrientation(verticalOrientation) {};

int Display::initialise() {
    return 1;
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
