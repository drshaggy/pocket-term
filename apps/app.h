#ifndef APP_H_
#define APP_H_

#include <iostream>
#include <queue>
#include "../drivers/display.h"
#include "../event.h"
#include "../ui.h"

class App
{
protected:
    UI& m_ui;
public:
    App(UI& ui);
    virtual ~App() = default;
    virtual int initialise();
    int processNextEvent(const Event e);
    virtual int processSpecificEvent(const Event& e);
};

#endif // APP_H_
