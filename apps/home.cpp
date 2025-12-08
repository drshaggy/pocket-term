#include "home.h"

int Home::initialise() {
    std::clog << "Home Initialised" << std::endl;
    m_ui.println("Pocket Terminal OS");
    m_ui.println("");
    m_ui.println(getCurrentTime());
    return 0;
}

int Home::processNextEvent(Event e) {
    return 0;
}

