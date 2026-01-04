#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include "app.h"

class Launcher : public App
{
private:
    uint8_t m_selectedApp {0};
    std::vector<std::string> m_appList{"Home", "Updater", "Calculator"};
public:
    Launcher(Actor& caller);
    int processSpecificMessage(Message& e) override;
};


#endif // LAUNCHER_H_
