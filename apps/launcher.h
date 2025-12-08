#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include "app.h"
#include <iostream>

class Launcher : public App
{
public:
    using App::App;
    int initialise() override;
    int processSpecificEvent(const Event& e) override;
};


#endif // LAUNCHER_H_
