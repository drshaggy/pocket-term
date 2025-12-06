#include "app.h"

App::App(Display& display) :
    m_display{display}
{};

int App::initialise(){
    return 1;
}

int App::sendKey(char key){
    //std::clog << "Sending key " << key << std::endl;
    m_keyQueue.push(key);
    return 0;
}

int App::processNextKey(){
    return 1;
}
