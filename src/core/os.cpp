#include "os.h"
#include "../apps/home.h"
#include "../input/input.h"
#include "../ui/ui.h"

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;
//
OS::OS()
    : Actor(),
      m_input(launchNestedActor<Input>(*this)),
      m_ui(launchNestedActor<UI>(*this)),
      m_currentApp(launchNestedActor<Home>(*this, m_ui))
      
{
    spdlog::info("PocketTerm OS Starting");
}

void OS::run() {
    while(true) {
        auto m = dequeue();
        if (m) {
            handleMessage(*m);
        }
        doActorCore();
    }
}

void OS::handleMessage(Message& m) {
    if (m.type == KEY_PRESS) {
        char key = static_cast<KeyMessageData&>(*m.data).getKey();
        spdlog::debug("Key {} received in OS by message", key);
        Message msg = Message::createAckMessage(true);
        sendMessage(m_input, msg);
        //clear screen on escape
        // if (key == '\x1b') {
        //     m_appManager.switchToApp(HOME);
        // } else {
        //     m_ui.print(std::string(1, key));
        // }
    }
}


void OS::doActorCore() {
    std::this_thread::sleep_for(10ms);
}
