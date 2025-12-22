#include "app.h"
#include "../core/app_manager.h"
#include "../ui/ui.h"

App::App(AppManager& appManager, UI& ui)
    : m_appManager{appManager},
      m_ui{ui}
{};

int App::initialise(){
    return 1;
}

//Message gets moved in to this function by design, tying the message lifetime to this functions  scope
int App::processNextMessage(Message e){
    if (e.type == KEY_PRESS) {
        char key = static_cast<KeyMessageData&>(*e.data).getKey();
        //clear screen on escape
        if (key == '\x1b') {
            m_appManager.switchToApp(HOME);
        } else {
            m_ui.print(std::string(1, key));
        }
        return 0;
    }
    processSpecificMessage(e);
    return 0;
}

// pass message by reference as unique pointer
int App::processSpecificMessage([[maybe_unused]]Message& e){
    return 1;
}

void App::updateUI(){
   m_ui.update();
}
