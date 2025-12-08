#include "app.h"

App::App(UI& ui) :
    m_ui{ui}
{};

int App::initialise(){
    return 1;
}

int App::processNextEvent(Event e){
    return 1;
}
