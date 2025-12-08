#include "ui.h"

void UI::print(const std::string& text){
    m_display.print(text);
}

void UI::printHighlighted(const std::string& text){
    m_display.printHighlighted(text);
}

void UI::println(const std::string& text){
    m_display.println(text);
}

void UI::clear() {
    m_display.clear();
}
