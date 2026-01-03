#include "app.h"
#include "../core/message.h"
#include "../config.h"

#include <spdlog/spdlog.h>

App::App(Actor& caller)
    : Actor(caller),
      m_currentScreen{Screen(SCREEN_WIDTH, SCREEN_HEIGHT - SEGMENT_HEIGHT)} 
{
    subscribe(KEY_PRESS);
};

int App::initialise(){
    return 1;
}

void App::handleMessage(Message& m){
    if (m.type == KEY_PRESS) {
        char key = static_cast<KeyMessageData&>(*m.data).getKey();
        //clear screen on escape
        if (key == '\x1b') {
            spdlog::debug("Escape Pressed");
            // m_appManager.switchToApp(HOME);
        }
    }
    processSpecificMessage(m);
}

// pass message by reference as unique pointer
int App::processSpecificMessage([[maybe_unused]]Message& m){
    return 1;
}

void App::updateUI(){
   //m_ui.update();
    Message m = createMessage<ScreenMessageData>(m_currentScreen);
    sendMessageToCaller(m);
}
