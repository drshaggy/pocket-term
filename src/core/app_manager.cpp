#include "actor.h"
#include "app_manager.h"
#include "../apps/home.h"
#include "../apps/app.h"

AppManager::AppManager(Actor& caller)
    : Actor(caller, "app_manager")
{
    // m_installedApps[HOME] = [this](Enqueuer ui){return std::make_unique<Home>(*this, ui);};
    // m_installedApps[LAUNCHER] = [this](Enqueuer ui){return std::make_unique<Launcher>(*this, ui);};
    subscribe(DOWN_KEY_PRESS);
    subscribe(UP_KEY_PRESS);
    launchApp<Home>();
};

void AppManager::handleMessage(Message& message) {
    Actor::handleMessage(message);
    switch(message.type) {
        case SCREEN:
            sendMessageToCaller(message);
            break;
        default:
            break;
    }
}

void AppManager::closeApp(Apps appId) {
}

void AppManager::switchToApp(Apps appId) {
    //m_lastApp = m_currentApp;
    //m_currentApp = appId;
}

