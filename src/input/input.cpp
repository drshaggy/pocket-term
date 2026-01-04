#include "input.h"
#include "../config.h"
#include "../enums.h"

#include "../drivers/cardkb.h"

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
        switch (input[0]) {
            case 0xB6: 
                m_logger->debug("DOWN Key Pressed");
                m = createMessage<SpecialKeyMessageData>(DOWN_KEY_PRESS);
                break;
            case 0xB5: 
                m_logger->debug("UP Key Pressed");
                m = createMessage<SpecialKeyMessageData>(UP_KEY_PRESS);
                break;
            case 0xB4: 
                m_logger->debug("LEFT Key Pressed");
                m = createMessage<SpecialKeyMessageData>(LEFT_KEY_PRESS);
                break;
            case 0xB7: 
                m_logger->debug("RIGHT Key Pressed");
                m = createMessage<SpecialKeyMessageData>(RIGHT_KEY_PRESS);
                break;
            case 0x1B: 
                m_logger->debug("ESCAPE Key Pressed");
                m = createMessage<SpecialKeyMessageData>(ESCAPE_KEY_PRESS);
                break;
            case 0x09: 
                m_logger->debug("TAB Key Pressed");
                m = createMessage<SpecialKeyMessageData>(TAB_KEY_PRESS);
                break;
            case 0x08: 
                m_logger->debug("BACKSPACE Key Pressed");
                m = createMessage<SpecialKeyMessageData>(BACKSPACE_KEY_PRESS);
                break;
            case 0x0D: 
                m_logger->debug("ENTER Key Pressed");
                m = createMessage<SpecialKeyMessageData>(ENTER_KEY_PRESS);
                break;
            default:
                m_logger->debug("{} Key Pressed", input[0]);
                m = createMessage<KeyMessageData>(input[0], 0);
                break;
        }
        sendMessageToCaller(m);
    }
}

void Input::handleMessage(Message& message) {
    if (message.type == ACKNOWLEDGE) {
        m_logger->debug("Ack Received");
    }
}
