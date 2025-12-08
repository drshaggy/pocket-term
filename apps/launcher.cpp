#include "launcher.h"

int Launcher::initialise(){
    std::clog << "Launcher Initialised" << std::endl;
    return 0;
}

int Launcher::processNextEvent(Event e){
    if (e.type == KEY_PRESS) {
        char key = static_cast<KeyEventData&>(*e.data).getKey();
        //clear screen on escape
        if (key == '\x1b') {
            m_ui.clear();
        } else {
            std::string pr;
            pr[0] = key;
            m_ui.print(pr);
        }
    }
    return 0;
}
