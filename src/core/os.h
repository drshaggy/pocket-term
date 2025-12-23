#ifndef OS_H_
#define OS_H_

#include <queue>
#include <memory>

#include "actor.h"
#include "app_manager.h"
#include "message.h"
#include "../ui/ui.h"
#include "../input/input.h"
#include "../drivers/cardkb.h"
#include "../drivers/sim800l.h"

class OS : public Actor
{
public:
    virtual ~OS();
    OS(const bool simulateHardware = true);
    void run();
protected:
    virtual void handleMessage(Message& message) override;
private:
    bool m_running;
    std::queue<Message> m_messageQueue;
    const bool m_simulateHardware;
    //Sim800l m_gsm;
    //CardKB m_keyboard; //Change to a vector of input devices OR message creators
    size_t m_input;
    size_t m_ui;
    //AppManager m_appManager;
    void setupLogging();
    void displayUpdateLoop();
};

#endif // OS_H_
