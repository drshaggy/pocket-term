#include "app.h"
#include "../core/message.h"
#include "../config.h"

#include <spdlog/spdlog.h>

App::App(Actor& caller, const std::string appName)
    : Actor(caller, appName),
      m_currentScreen{Screen(SCREEN_WIDTH, SCREEN_HEIGHT - SEGMENT_HEIGHT)} 
{
    subscribe(KEY_PRESS);
};

int App::initialise(){
    return 1;
}

void App::handleMessage(Message& message){
    Actor::handleMessage(message);
}

// pass message by reference as unique pointer
int App::processSpecificMessage([[maybe_unused]]Message& m){
    return 1;
}

void App::updateUI(){
   //m_ui.update();
    Message m = createMessage<ScreenMessageData>(m_currentScreen);
    sendMessageToCaller(m);
}
