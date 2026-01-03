#ifndef UI_H_
#define UI_H_

#include "../drivers/display.h"
#include "../core/actor.h"
#include "screen.h"
#include "status_bar.h"

#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

class UI : public Actor
{
private:
    std::unique_ptr<Display> m_display;

    //async statusBar
    StatusBar m_statusBar;

    //async screen
    Screen m_currentScreen;
    std::mutex m_screenMutex;
    std::condition_variable m_screenChanged;

    //async display
    bool m_pendingUpdate = false;
    std::atomic<bool> m_displayUpdateRunning;
    std::thread m_displayUpdateThread;
    void displayThreadLoop();
    
    void updateStatusBar();
    void update(Screen& screen);
    void clear();
    
    virtual void setUp() override;
    virtual void doActorCore() override;
    virtual void handleMessage(Message& message) override;
public:
    UI();
    UI(Actor& caller);
    virtual ~UI();
};

#endif // UI_H_
