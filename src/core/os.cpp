#include "os.h"
#include "../apps/home.h"
#include "../input/input.h"
#include "../ui/ui.h"

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;
//
OS::OS()
    : Actor("os")   
{
    spdlog::info("PocketTerm OS Starting");
}

void OS::handleMessage(Message& m) {
    Actor::handleMessage(m);
    if (m.type == KEY_PRESS) {
        char key = static_cast<KeyMessageData&>(*m.data).getKey();
        spdlog::debug("Key {} received in OS by message", key);
    }
}

void OS::setUp() {
    m_input = launchNestedActor<Input>(*this);
    m_ui = launchNestedActor<UI>(*this);
    m_currentApp = launchNestedActor<Home>(*this);  
}

void OS::doActorCore() {
    std::this_thread::sleep_for(10ms);
}
