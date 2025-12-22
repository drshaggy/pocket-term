#include "message.h"

Message Message::createKeyMessage(char key, uint32_t ts) {
   Message m;
   m.type = KEY_PRESS;
   m.data = std::make_unique<KeyMessageData>(key, ts);
   return m;
}
