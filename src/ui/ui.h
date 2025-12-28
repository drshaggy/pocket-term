#ifndef UI_H_
#define UI_H_

#include "../drivers/display.h"
#include "../core/actor.h"
#include "screen.h"

#include <memory>

class UI : public Actor
{
private:
    std::unique_ptr<Display> m_display;
    Screen m_currentScreen;
    std::mutex m_screenMutex;
    bool m_pendingUpdate = false;
    std::condition_variable m_screenChanged;
    std::atomic<bool> m_displayUpdateRunning;
    std::thread m_displayUpdateThread;
    void displayThreadLoop();
protected:
    virtual void setUp() override;
    virtual void doActorCore() override;
    virtual void handleMessage(Message& message) override;
public:
    UI();
    UI(Actor& caller);
    virtual ~UI();
    void clear();
    void update(Screen& screen);
};

#endif // UI_H_
