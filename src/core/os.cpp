#include "os.h"
#include "../input/input.h"
#include "../ui/ui.h"
#include "app_manager.h"

using namespace std::chrono_literals;
//
OS::OS()
    : Actor("os")   
{
    m_logger->info("PocketTerm OS Starting");
}

void OS::handleMessage(Message& m) {
    Actor::handleMessage(m);
    if (m.type == KEY_PRESS) {
        char key = static_cast<KeyMessageData&>(*m.data).getKey();
        m_logger->debug("Key {} received in OS by message", key);
    }
}

void OS::setUp() {
    m_input = launchNestedActor<Input>(*this);
    m_ui = launchNestedActor<UI>(*this);
    m_appManager = launchNestedActor<AppManager>(*this);
}

void OS::doActorCore() {
    std::this_thread::sleep_for(10ms);
}
