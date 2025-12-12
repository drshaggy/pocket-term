#include "home.h"

#include "../utilities.h"
#include "../ui/ui.h"

#include <iostream>

int Home::initialise() {
    std::clog << "Home Initialised" << std::endl;
    m_ui.clear();
    m_ui.println("Pocket Terminal OS");
    m_ui.println("");
    m_ui.print(getCurrentTime());
    m_ui.print("  ");
    m_ui.printHighlighted(getCurrentDate());
    return 0;
}

int Home::processSpecificEvent(Event& e) {
    return 0;
}

