#include "ui.h"
#include "../drivers/waveshare_eink.h"
#include "../drivers/tty_display.h"
#include "../config.h"
#include "../core/message.h"

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

UI::UI(Actor& caller)
    : Actor(caller)
{
    if (SIMULATE_HARDWARE) {
        m_display = std::make_unique<TtyDisplay>(false);
    } else {
        m_display = std::make_unique<WaveshareEink>(false);
    }
}

void UI::setUp() {
    subscribe(SCREEN);
}

void UI::doActorCore() {
        std::this_thread::sleep_for(1000ms);
}

void UI::handleMessage(Message& message) {
    spdlog::debug("UI handleMessage Called");
    Actor::handleMessage(message);
    if (message.type == SCREEN) {
       m_currentScreen = static_cast<ScreenMessageData&>(*message.data).getScreen();
       update();
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
    m_display->draw(m_currentScreen);
    m_display->redraw();
}
