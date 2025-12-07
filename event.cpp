#include "event.h"

Event Event::createKeyEvent(char key, uint32_t ts) {
   Event e;
   e.type = KEY_PRESS;
   e.data = std::make_unique<KeyEventData>(key, ts);
   return e;
}
