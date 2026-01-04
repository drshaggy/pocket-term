#include "home.h"
#include "../ui/text_widget.h"
#include "../ui/vertical_widget.h"
#include "../ui/screen.h"

using namespace std::chrono_literals;

Home::Home(Actor& caller)
    : App(caller, "home")
{ 
    m_logger->info("Initialising Home App...");

    
    std::unique_ptr<Widget> text = std::make_unique<TextWidget>("HOME", false);
    std::unique_ptr<VerticalWidget> vert = std::make_unique<VerticalWidget>();
    vert->add(text);
    m_currentScreen.setRootWidget(std::move(vert));
    //std::this_thread::sleep_for(5000ms);
    updateUI();
    subscribe(DOWN_KEY_PRESS);
    subscribe(UP_KEY_PRESS);
    m_logger->info("Home App Initilialised");
}

void Home::handleMessage(Message& m) {
    App::handleMessage(m);
    m_logger->debug("Home Received Message type");
    switch(m.type) {
        case DOWN_KEY_PRESS: {
            if(m_selectedApp < m_appList.size()-1) {
                m_selectedApp += 1;
            } else {
                m_selectedApp = 0;
            }
            break;
        }
        case UP_KEY_PRESS: {
            if(m_selectedApp > 0) {
                m_selectedApp -= 1;
            } else {
                m_selectedApp = m_appList.size()-1;
            }
            break;
        }
        default: {
            break;
        }
    }
}

