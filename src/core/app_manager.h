#ifndef APP_MANAGER_H_
#define APP_MANAGER_H_

#include <map>
#include <functional>

#include "../apps/app.h"
#include "actor.h"

enum Apps {
	EMPTY,
	HOME,
	LAUNCHER
};



class AppManager : public Actor
{
public:
    AppManager(Actor& caller, Enqueuer ui);
    void launchApp(Apps appId);
    void closeApp(Apps appId);
    void switchToApp(Apps appId);
    App& getCurrentApp() {return *m_runningApps[m_currentApp];};
private:
    Enqueuer m_ui;
    Apps m_currentApp;
    Apps m_lastApp;
    std::map<Apps, std::unique_ptr<App>> m_runningApps;
    std::map<Apps, std::function<std::unique_ptr<App>(Actor& caller, Enqueuer ui)>> m_installedApps;
};

#endif // APP_MANAGER_H_
