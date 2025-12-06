#include "launcher.h"

Launcher::Launcher(Display& display) :
    App(display)
{};

int Launcher::initialise(){
    std::clog << "Launcher Initialised" << std::endl;
    return 0;
}

int Launcher::processNextKey(){
    if(m_keyQueue.front() == '\x1b' ){
        m_display.clear();
    }
    return 0;
}
