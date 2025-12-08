#include "app.h"

App::App(UI& ui) :
    m_ui{ui}
{};

int App::initialise(){
    return 1;
}

//Event gets moved in to this function by design, tying the event lifetime to this functions  scope
int App::processNextEvent(const Event e){
    if (e.type == KEY_PRESS) {
        char key = static_cast<KeyEventData&>(*e.data).getKey();
        //clear screen on escape
        if (key == '\x1b') {
            m_ui.clear();
        } else {
            m_ui.print(std::string(1, key));
        }
        return 0;
    }
    processSpecificEvent(e);
    return 0;
}

// pass event by reference as unique pointer
int App::processSpecificEvent(const Event& e){
    return 1;
}
