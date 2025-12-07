#include "app.h"

App::App(Display& display) :
    m_display{display}
{};

int App::initialise(){
    return 1;
}

int App::processNextEvent(Event e){
    return 1;
}
