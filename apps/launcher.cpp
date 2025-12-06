#include "launcher.h"

Launcher::Launcher(Display& display) :
    App(display)
{};

int Launcher::initialise(){
    std::clog << "Launcher Initialised" << std::endl;
    return 0;
}

int Launcher::processNextKey(){
    std::clog << "processing key " << m_keyQueue.front() << std::endl;
    if(m_keyQueue.front() == '\x1b' ){
        std::clog << "escape pressed" << std::endl;
        m_display.clear();
    }
    m_keyQueue.pop();
    return 0;
}
