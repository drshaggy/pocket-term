#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include "app.h"
#include <iostream>

class Launcher : public App
{
public:
    using App::App;
    Launcher(Display& display);
    int initialise() override;
    int processNextEvent(Event e) override;
};


#endif // LAUNCHER_H_
