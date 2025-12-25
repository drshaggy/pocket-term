#ifndef APP_H_
#define APP_H_

#include "../core/message.h"
#include "../core/actor.h"

class AppManager;
class UI;

class App : public Actor
{
protected:
    Enqueuer m_ui;
public:
    App(Actor& caller, Enqueuer ui);
    virtual ~App() = default;
    virtual int initialise();
    int processNextMessage(Message e);
    virtual int processSpecificMessage(Message& e);
    void updateUI();
    
    virtual void handleMessage(Message& e);
};

int switchApp(std::unique_ptr<App> newApp); //do we use a map to hold installed apps that are registered? and use this is restore an app if required
                                            //
#endif // APP_H_
