#ifndef OS_H_
#define OS_H_

#include <queue>
#include <memory>

#include "actor.h"
#include "app_manager.h"
#include "event.h"
#include "../ui/ui.h"
#include "../input/input.h"
#include "../drivers/cardkb.h"
#include "../drivers/sim800l.h"

class OS : Actor
{
public:
    OS();
    ~OS();
    OS(const bool simulateHardware);
    void run();
private:
    std::queue<Event> m_eventQueue;
    const bool m_simulateHardware;
    //Sim800l m_gsm;
    //CardKB m_keyboard; //Change to a vector of input devices OR event creators
    std::unique_ptr<Input> m_input;
    std::unique_ptr<UI> m_ui;
    //AppManager m_appManager;
    void setupLogging();
    void displayUpdateLoop();
};

#endif // OS_H_
