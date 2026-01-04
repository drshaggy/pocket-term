#include "input.h"
#include "../config.h"
#include "../enums.h"

#include "../drivers/cardkb.h"
#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

Input::Input(Actor& caller)
    : Actor(caller, "input")
{
    if (SIMULATE_HARDWARE) {
        m_keyboard = std::make_unique<Keyboard>();
    } else {
        m_keyboard = std::make_unique<CardKB>(uint8_t(0x5f));
    }
}

void Input::doActorCore() {
    unsigned char input[256];
    input[0] = 0;
    input[0] = m_keyboard->read();
    std::this_thread::sleep_for(20ms);
    if (input[0]) {
        Message m;
        spdlog::debug("Input: 0x{:02X}, is Down? {}", input[0], input[0] == 0xB6);
        switch (input[0]) {
            case 0xB6: 
                spdlog::debug("DOWN Key Pressed");
                m = createMessage<SpecialKeyMessageData>(DOWN_KEY_PRESS);
                break;
            case 0xB5: 
                spdlog::debug("UP Key Pressed");
                m = createMessage<SpecialKeyMessageData>(UP_KEY_PRESS);
                break;
            case 0xB4: 
                spdlog::debug("LEFT Key Pressed");
                m = createMessage<SpecialKeyMessageData>(LEFT_KEY_PRESS);
                break;
            case 0xB7: 
                spdlog::debug("RIGHT Key Pressed");
                m = createMessage<SpecialKeyMessageData>(RIGHT_KEY_PRESS);
                break;
            case 0x1B: 
                spdlog::debug("ESCAPE Key Pressed");
                m = createMessage<SpecialKeyMessageData>(ESCAPE_KEY_PRESS);
                break;
            case 0x09: 
                spdlog::debug("TAB Key Pressed");
                m = createMessage<SpecialKeyMessageData>(TAB_KEY_PRESS);
                break;
            case 0x08: 
                spdlog::debug("BACKSPACE Key Pressed");
                m = createMessage<SpecialKeyMessageData>(BACKSPACE_KEY_PRESS);
                break;
            case 0x0D: 
                spdlog::debug("ENTER Key Pressed");
                m = createMessage<SpecialKeyMessageData>(ENTER_KEY_PRESS);
                break;
            default:
                spdlog::debug("{} Key Pressed", input[0]);
                m = createMessage<KeyMessageData>(input[0], 0);
                break;
        }
        sendMessageToCaller(m);
    }
}

void Input::handleMessage(Message& message) {
    if (message.type == ACKNOWLEDGE) {
        spdlog::debug("Ack Received");
    }
}
