#include "launcher.h"
#include "../ui/list_widget.h"
#include "../ui/vertical_widget.h"

Launcher::Launcher(Actor& caller) : App(caller, "launcher")
{
    m_logger->info("Initialising Launcher App...");

    std::unique_ptr<Widget> list = std::make_unique<ListWidget>(m_appList, m_selectedApp);
    std::unique_ptr<VerticalWidget> vert = std::make_unique<VerticalWidget>();
    vert->add(list);
    m_currentScreen.setRootWidget(std::move(vert));
    //std::this_thread::sleep_for(5000ms);
    updateUI();
    subscribe(DOWN_KEY_PRESS);
    subscribe(UP_KEY_PRESS);

    m_logger->info("Launcher App Initilialised");
    
}


int Launcher::processSpecificMessage(Message& e){
    if (e.type == KEY_PRESS) {
        char key = static_cast<KeyMessageData&>(*e.data).getKey();
        //clear screen on escape
        if (key == '\x1b') {
            //m_ui.clear();
        } else {
            //m_ui.print(std::string(1, key));
        }
    }
    return 0;
}
