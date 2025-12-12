#include "ui.h"
#include "drivers/tty_display.h"

UI::UI() {
    m_display = std::make_unique<TtyDisplay>();
    if (m_display->initialise()){
        std::cerr << "Failed to initialise display" << std::endl;
    }
}

void UI::print(const std::string& text){
    m_display->print(text);
}

void UI::printHighlighted(const std::string& text){
    m_display->printHighlighted(text);
}

void UI::println(const std::string& text){
    m_display->println(text);
}

void UI::clear() {
    m_display->clear();
}

void UI::update() {

}
