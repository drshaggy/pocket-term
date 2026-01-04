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
    spdlog::info("Home App Initilialised");
}

int Home::initialise() {
    return 0;
}

int Home::processSpecificMessage(Message& m) {
    spdlog::debug("Received Message");
    switch(m.type) {
        case KEY_PRESS: {
            auto* keyData = static_cast<KeyMessageData*>(m.data.get()); 
            char key = keyData->getKey();
            if (key == '\xB6') {
                spdlog::debug("Down Arrow Pressed");
                if(m_selectedApp < m_appList.size()-1) {
                    m_selectedApp += 1;
                } else {
                    m_selectedApp = 0;
                }
            } else {
                input += key;
                std::unique_ptr<Widget> text = std::make_unique<TextWidget>(input, false);
                m_currentScreen.setRootWidget(std::move(text));
                updateUI();
            }
        }
        default: {
            
        }
    }
    return 0;
    
}

