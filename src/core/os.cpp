#include "os.h"
#include "actor.h"

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;
//
OS::OS(const bool simulateHardware)
    : m_simulateHardware(simulateHardware),
      m_input(launchActor<Input>()),
      m_ui(launchActor<UI>())
{
    spdlog::info("PocketTerm OS Starting");
}

OS::~OS() {
    m_running = false;
}


void OS::run() {
    m_running = true;
    while(m_running) {
        spdlog::debug("Main loop Running");
        std::this_thread::sleep_for(100ms);
    }
}

