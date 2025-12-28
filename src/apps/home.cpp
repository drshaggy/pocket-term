#include "home.h"
#include "../ui/text_widget.h"
#include "../ui/vertical_widget.h"
#include "../ui/screen.h"

#include <spdlog/spdlog.h>
#include <thread>

using namespace std::chrono_literals;

Home::Home(Actor& caller)
    : App(caller)
{ 
    spdlog::info("Home App Initilialised");
    std::unique_ptr<Widget> text = std::make_unique<TextWidget>("Hello World", false);
    std::unique_ptr<Widget> text2 = std::make_unique<TextWidget>("New line", false);
    std::unique_ptr<VerticalWidget> vert = std::make_unique<VerticalWidget>();
    vert->add(text);
    vert->add(text2);
    m_currentScreen.setRootWidget(std::move(vert));
    std::this_thread::sleep_for(5000ms);
    updateUI();
}

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

int Home::processSpecificMessage(Message& m) {
    spdlog::debug("Received Message");
    switch(m.type) {
        case KEY_PRESS: {
            auto* keyData = static_cast<KeyMessageData*>(m.data.get()); 
            char key = keyData->getKey();
            input += key;
            std::unique_ptr<Widget> text = std::make_unique<TextWidget>(input, false);
            m_currentScreen.setRootWidget(std::move(text));
            updateUI();
            //m_ui.print(std::string() + key);
            //m_ui.update();
        }
        case TICK: {
            
        }
    }
    return 0;
    
}

