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

int switchApp(std::unique_ptr<App> newApp); //do we use a map to hold installed apps that are registered? and use this is restore an app if required
                                            //
#endif // APP_H_
