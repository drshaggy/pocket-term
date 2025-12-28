#include "input.h"
#include "../config.h"

#include "../drivers/cardkb.h"
#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

Input::Input(Actor& caller)
    : Actor(caller)
{
    if (SIMULATE_HARDWARE) {
        m_keyboard = std::make_unique<Keyboard>();
    } else {
        m_keyboard = std::make_unique<CardKB>(uint8_t(0x5f));
    }
}

void Input::doActorCore() {
    char input[256];
    input[0] = 0;
    input[0] = m_keyboard->read();
    std::this_thread::sleep_for(20ms);
    if (input[0]) {
        Message m = createMessage<KeyMessageData>(input[0], 0);
        sendMessageToCaller(m);
        spdlog::debug("Key {} pressed in input actor", input);
    }
}

void Input::handleMessage(Message& message) {
    if (message.type == ACKNOWLEDGE) {
        spdlog::debug("Ack Received");
    }
}
