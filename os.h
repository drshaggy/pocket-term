#ifndef OS_H_
#define OS_H_

#include <iostream>
#include <queue>

#include "event.h"
#include "ui.h"
#include "drivers/cardkb.h"
#include "drivers/tty_display.h"
#include "apps/home.h"

class OS
{
public:
    OS();
    void run();
    void cleanUp();
private:
    std::unique_ptr<App> m_currentApp;
    UI m_ui;
    std::queue<Event> m_eventQueue;
    CardKB m_keyboard; //Change to a vector of input devices OR event creators
    std::unique_ptr<Display> m_display;
};

#endif // OS_H_
