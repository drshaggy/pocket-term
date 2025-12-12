#ifndef APP_H_
#define APP_H_

#include "../event.h"

class AppManager;
class UI;

class App
{
protected:
    AppManager& m_appManager;
    UI& m_ui;
public:
    App(AppManager& appManager, UI& ui);
    virtual ~App() = default;
    virtual int initialise();
    int processNextEvent(Event e);
    virtual int processSpecificEvent(Event& e);
    void updateUI();
};

int switchApp(std::unique_ptr<App> newApp); //do we use a map to hold installed apps that are registered? and use this is restore an app if required
                                            //
#endif // APP_H_
