#ifndef OS_H_
#define OS_H_

#include <queue>
#include <thread>
#include <atomic>

#include "app_manager.h"
#include "event.h"
#include "../ui/ui.h"
#include "../drivers/cardkb.h"
#include "../drivers/sim800l.h"

class OS
{
public:
    OS();
    void run();
    void cleanUp();
private:
    std::queue<Event> m_eventQueue;
    Sim800l m_gsm;
    CardKB m_keyboard; //Change to a vector of input devices OR event creators
    UI m_ui;
    AppManager m_appManager;
    void setupLogging();
    std::thread m_displayThread;
    std::atomic<bool> m_running;
    void displayUpdateLoop();
};

#endif // OS_H_
