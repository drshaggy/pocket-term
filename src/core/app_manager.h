#ifndef APP_MANAGER_H_
#define APP_MANAGER_H_

#include <map>
#include <functional>

#include "../apps/app.h"
#include "actor.h"
#include "../enums.h"


class AppManager : public Actor
{
public:
    AppManager(Actor& caller);
    virtual void handleMessage(Message& message) override;
    template<typename AppType>
    void launchApp() {
        m_currentApp = launchNestedActor<AppType>(*this);
    }
    void closeApp();
    void switchToApp();
private:
    Enqueuer m_currentApp;
    Enqueuer m_lastApp;
    std::map<Apps, std::unique_ptr<App>> m_runningApps;
    std::map<Apps, std::function<std::unique_ptr<App>(Actor& caller, Enqueuer ui)>> m_installedApps;
};

#endif // APP_MANAGER_H_
