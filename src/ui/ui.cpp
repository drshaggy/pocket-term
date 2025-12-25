#include "ui.h"
#include "../drivers/waveshare_eink.h"
#include "../drivers/tty_display.h"

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

UI::UI(Actor& caller)
    : Actor(caller)
{
    if (false) {
        m_display = std::make_unique<WaveshareEink>(false);
    } else {
        m_display = std::make_unique<TtyDisplay>(false);
    }
}

void UI::doActorCore() {
        std::this_thread::sleep_for(1000ms);
}

void UI::handleMessage(Message& message) {
    if (message.type == SCREEN) {
       m_currentScreen = static_cast<ScreenMessageData&>(*message.data).getScreen();
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
    m_display->redraw();
}
