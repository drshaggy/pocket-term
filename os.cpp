#include "os.h"

OS::OS()
    : m_keyboard(CardKB(uint8_t(0x5f))),
      m_ui(UI()),
      m_appManager(m_ui)
{
    //move these inits in to constructors
    if (m_keyboard.initialise()){
        std::cerr << "Failed to initialise keyboard" << std::endl;
    }
}

void OS::run() {
    while(true) {
        //poll all the event sources
        m_keyboard.poll();
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
    m_keyboard.end();
}
