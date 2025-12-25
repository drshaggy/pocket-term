#include "app.h"

App::App(Actor& caller, Enqueuer ui)
    : Actor(caller),
      m_ui{ui}
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
}
