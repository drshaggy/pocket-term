#include "launcher.h"

Launcher::Launcher(Display& display) :
    App(display)
{};

int Launcher::initialise(){
    std::clog << "Launcher Initialised" << std::endl;
    return 0;
}

int Launcher::processNextEvent(Event e){
    if (e.type == KEY_PRESS) {
        char key = static_cast<KeyEventData&>(*e.data).getKey();
        //clear screen on escape
        if (key == '\x1b') {
            m_display.clear();
        } else {
            std::cout << key << std::flush;
        }
    }
    return 0;
}
