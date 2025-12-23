#include "os.h"

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;
//
OS::OS(const bool simulateHardware)
    : m_running {false},
      m_simulateHardware(simulateHardware),
      m_input(launchNestedActor<Input>()),
      m_ui(launchNestedActor<UI>())
{
    spdlog::info("PocketTerm OS Starting");
}

OS::~OS() {
    m_running = false;
}


void OS::run() {
    m_running = true;
    while(m_running) {
        auto m = dequeue();
        if (m) {
            handleMessage(*m);
        }
        std::this_thread::sleep_for(10ms);
    }
}

void OS::handleMessage(Message& m) {
    if (m.type == KEY_PRESS) {
        char key = static_cast<KeyMessageData&>(*m.data).getKey();
        spdlog::debug("Key {} received in OS by message", key);
        //clear screen on escape
        // if (key == '\x1b') {
        //     m_appManager.switchToApp(HOME);
        // } else {
        //     m_ui.print(std::string(1, key));
        // }
    }
}
