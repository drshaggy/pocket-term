#include "home.h"

#include "../core/time_utils.h"
#include "../ui/ui.h"

#include <spdlog/spdlog.h>

int Home::initialise() {
    spdlog::info("Home App Initilialised");
    //m_ui.clear();
    //m_ui.println("Pocket Terminal OS");
    //m_ui.println("");
    //m_ui.print(getCurrentTime());
    //m_ui.print("  ");
    //m_ui.printHighlighted(getCurrentDate());
    //m_ui.update();
    return 0;
}

int Home::processSpecificMessage(Message& e) {
    spdlog::debug("Received Message");
    switch(e.type) {
        case KEY_PRESS: {
            auto* keyData = static_cast<KeyMessageData*>(e.data.get()); 
            char key = keyData->getKey();
            //m_ui.print(std::string() + key);
            //m_ui.update();
        }
        case TICK: {
            
        }
    }
    return 0;
    
}

