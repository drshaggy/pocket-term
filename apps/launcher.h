#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include "app.h"
#include <iostream>

class Launcher : public App
{
public:
    Launcher(Display& display);
    int initialise() override;
    int processNextKey() override;
};


#endif // LAUNCHER_H_
