#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include "app.h"

class Launcher : public App
{
public:
    using App::App;
    int initialise() override;
    int processSpecificMessage(Message& e) override;
};


#endif // LAUNCHER_H_
