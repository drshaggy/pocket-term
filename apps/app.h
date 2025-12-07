#ifndef APP_H_
#define APP_H_

#include <iostream>
#include <queue>
#include "../drivers/display.h"
#include "../event.h"

class App
{
protected:
    Display& m_display;
public:
    App(Display& display);
    virtual ~App() = default;
    virtual int initialise();
    virtual int processNextEvent(Event e);
};

#endif // APP_H_
