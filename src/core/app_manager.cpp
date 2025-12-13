#include <memory>

#include "../ui/ui.h"
#include "app_manager.h"
#include "../apps/home.h"
#include "../apps/launcher.h"
#include "../apps/app.h"

AppManager::AppManager(UI& ui)
    : m_ui(ui),
      m_currentApp(HOME)
{
    m_installedApps[HOME] = [this](UI& ui){return std::make_unique<Home>(*this, ui);};
    m_installedApps[LAUNCHER] = [this](UI& ui){return std::make_unique<Launcher>(*this, ui);};

    launchApp(HOME);
};

void AppManager::launchApp(Apps appId) {
     m_runningApps[appId] = m_installedApps[appId](m_ui);
     m_runningApps[appId]->initialise();
     m_currentApp = appId;
}

void AppManager::closeApp(Apps appId) {
    if (m_runningApps.contains(appId)) {
        m_runningApps.erase(appId);
    }
}

void AppManager::switchToApp(Apps appId) {
    m_lastApp = m_currentApp;
    m_currentApp = appId;
}

