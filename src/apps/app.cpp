#include "app.h"
#include "../core/message.h"


App::App(Actor& caller)
    : Actor(caller),
      m_currentScreen{Screen(uint8_t(800), uint8_t(480))} 
{};

int App::initialise(){
    return 1;
}

void App::handleMessage(Message& m){
    if (m.type == KEY_PRESS) {
        char key = static_cast<KeyMessageData&>(*m.data).getKey();
        //clear screen on escape
        if (key == '\x1b') {
            // m_appManager.switchToApp(HOME);
        } else {
            //m_ui.print(std::string(1, key));
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
