#include "os.h"

#include <thread>

using namespace std::chrono_literals;
//
OS::OS()
    : m_gsm(Sim800l("/dev/serial0", 9600)),
      m_keyboard(CardKB(uint8_t(0x5f))),
      m_ui(UI()),
      m_appManager(m_ui)
{
}


void OS::run() {
    m_running = true;

    m_displayThread = std::thread(&OS::displayUpdateLoop, this);
    
    while(m_running) {
        //poll all the event sources
        m_keyboard.poll();
        m_gsm.poll();
        if (m_keyboard.hasEvents()) {
            m_eventQueue.push(m_keyboard.getNextEvent());
        }
        if (!m_eventQueue.empty()) {
            m_appManager
                .getCurrentApp()
                .processNextEvent(std::move(m_eventQueue.front()));
            m_eventQueue.pop();
        }
        std::this_thread::sleep_for(10ms);
    }
}

void OS::cleanUp() {
    m_running = false;
    if (m_displayThread.joinable()) {
        m_displayThread.join();
    }
    
    m_keyboard.end();
}

void OS::displayUpdateLoop() {
    while (m_running) {
        m_ui.update();
        std::this_thread::sleep_for(10ms);
    }
}
