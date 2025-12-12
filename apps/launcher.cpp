#include "launcher.h"
#include "../ui/ui.h"
#include <spdlog/spdlog.h>

int Launcher::initialise(){
    spdlog::info("Launcher App Initilialised");
    return 0;
}

int Launcher::processSpecificEvent(Event& e){
    if (e.type == KEY_PRESS) {
        char key = static_cast<KeyEventData&>(*e.data).getKey();
        //clear screen on escape
        if (key == '\x1b') {
            m_ui.clear();
        } else {
            m_ui.print(std::string(1, key));
        }
    }
    return 0;
}
