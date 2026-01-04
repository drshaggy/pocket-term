#ifndef OS_H_
#define OS_H_

#include <queue>

#include "actor.h"
#include "message.h"

class OS : public Actor
{
public:
    virtual ~OS() = default;
    OS();
protected:
    virtual void handleMessage(Message& message) override;
    virtual void doActorCore() override;
    virtual void setUp() override;
private:
    std::queue<Message> m_messageQueue;
    //Sim800l m_gsm;
    //CardKB m_keyboard; //Change to a vector of input devices OR message creators
    Enqueuer m_input;
    Enqueuer m_ui;
    Enqueuer m_currentApp;
    Enqueuer m_appManager;
    void setupLogging();
    void displayUpdateLoop();
};

#endif // OS_H_
