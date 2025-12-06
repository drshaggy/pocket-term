#include "launcher.h"

Launcher::Launcher(Display& display) :
    App(display)
{};

int Launcher::initialise(){
    std::clog << "Launcher Initialised" << std::endl;
    return 0;
}
