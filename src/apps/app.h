#ifndef APP_H_
#define APP_H_

#include "../core/message.h"
#include "../core/actor.h"
#include "../ui/screen.h"


class AppManager;
class UI;

class App : public Actor
{
protected:
    Screen m_currentScreen;
public:
    App(Actor& caller);
    virtual ~App() = default;
    virtual int initialise();
    int processNextMessage(Message e);
    virtual int processSpecificMessage(Message& e);
    void updateUI();
    
    virtual void handleMessage(Message& message) override;
};

int switchApp(std::unique_ptr<App> newApp); //do we use a map to hold installed apps that are registered? and use this is restore an app if required
                                            //
#endif // APP_H_
