#include "input.h"

#include "../drivers/cardkb.h"

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

Input::Input()
    : Actor()
{
    if (false) {
        m_keyboard = std::make_unique<CardKB>(uint8_t(0x5f));
    } else {
        m_keyboard = std::make_unique<Keyboard>();
    }
}

void Input::actorCore() {
    char input[256];
    input[0] = 0;
    input[0] = m_keyboard->read();
    std::this_thread::sleep_for(20ms);
    if (input[0]) {
        Message m = Message::createKeyMessage(input[0], 0);
        sendMessageToParent(m);
        spdlog::debug("Key {} pressed in input actor", input);
    }
}

void Input::handleMessage(Message& message) {}
