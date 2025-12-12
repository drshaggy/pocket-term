#ifndef OS_H_
#define OS_H_

#include <queue>

#include "app_manager.h"
#include "event.h"
#include "ui/ui.h"
#include "drivers/cardkb.h"

class OS
{
public:
    OS();
    void run();
    void cleanUp();
private:
    std::queue<Event> m_eventQueue;
    CardKB m_keyboard; //Change to a vector of input devices OR event creators
    UI m_ui;
    AppManager m_appManager;
};

#endif // OS_H_
