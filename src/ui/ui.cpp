#include "ui.h"
#include "../drivers/waveshare_eink.h"

#include <spdlog/spdlog.h>

UI::UI() {
    m_display = std::make_unique<WaveshareEink>(false);
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
    m_display->redraw();
}
