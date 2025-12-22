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
        spdlog::debug("Actor {} Running", getActorId());
        std::this_thread::sleep_for(100ms);
    }
}

