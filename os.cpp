#include "os.h"

OS::OS()
    : m_ui(UI()),
      m_keyboard(CardKB(uint8_t(0x5f))),
      m_currentApp(std::make_unique<App>(m_ui))
{
    //move these inits in to constructors
    if (m_keyboard.initialise()){
        std::cerr << "Failed to initialise keyboard" << std::endl;
    }
    if(m_currentApp->initialise()){
       std::cerr << "Default app failed to load" << std::endl;
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
            m_currentApp->processNextEvent(std::move(m_eventQueue.front()));
            m_eventQueue.pop();
        }
        std::this_thread::sleep_for(10ms);
    }
}

void OS::cleanUp() {
    m_keyboard.end();
}
