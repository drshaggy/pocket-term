#include "home.h"
#include "../ui/text_widget.h"
#include "../ui/list_widget.h"
#include "../ui/vertical_widget.h"
#include "../ui/screen.h"

#include <spdlog/spdlog.h>
#include <thread>

using namespace std::chrono_literals;

Home::Home(Actor& caller)
    : App(caller)
{ 
    spdlog::info("Initialising Home App...");

    
    std::unique_ptr<Widget> list = std::make_unique<ListWidget>(m_appList, m_selectedApp);
    std::unique_ptr<VerticalWidget> vert = std::make_unique<VerticalWidget>();
    vert->add(list);
    m_currentScreen.setRootWidget(std::move(vert));
    std::this_thread::sleep_for(5000ms);
    updateUI();
    subscribe(DOWN_KEY_PRESS);
    subscribe(UP_KEY_PRESS);
    spdlog::info("Home App Initilialised");
}

int Home::initialise() {
    return 0;
}

void Home::handleMessage(Message& m) {
    spdlog::debug("Home Received Message type");
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

