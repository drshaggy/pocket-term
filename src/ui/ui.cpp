#include "ui.h"
#include "../drivers/waveshare_eink.h"
#include "../drivers/tty_display.h"
#include "../config.h"
#include "../core/message.h"


#include <memory>
#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

UI::UI(Actor& caller)
    : Actor(caller)
{
    if (SIMULATE_HARDWARE) {
        m_display = std::make_unique<TtyDisplay>(false);
    } else {
        m_display = std::make_unique<WaveshareEink>(false);
    }
    m_displayUpdateRunning = true;
    m_displayUpdateThread = std::thread(&UI::displayThreadLoop, this);
    m_statusBar = StatusBar(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (m_display->isReady()) {
        updateStatusBar();
    }
    
    
}

UI::~UI()
{
    m_displayUpdateRunning = false;  
    m_screenChanged.notify_one();
    if (m_displayUpdateThread.joinable()) {
        m_displayUpdateThread.join();
    }
}

void UI::setUp() {
    subscribe(SCREEN);
}

void UI::doActorCore() {
        std::this_thread::sleep_for(100ms);
}

void UI::handleMessage(Message& message) {
    spdlog::debug("UI handleMessage Called");
    Actor::handleMessage(message);
    if (message.type == SCREEN) {
        {
            std::lock_guard<std::mutex> lock(m_screenMutex);
            m_currentScreen = static_cast<ScreenMessageData&>(*message.data).getScreen();
            m_pendingUpdate = true;
        } //release lock
        m_screenChanged.notify_one();
    }
}

void UI::clear() {
    m_display->clear();
}

void UI::update(Screen& screen) {
    m_display->draw(screen);
    m_display->refresh();
}

void UI::updateStatusBar() {
    m_display->draw(m_statusBar);
    m_display->refresh();
}

void UI::displayThreadLoop() {
    while (m_displayUpdateRunning) {
       Screen screenToDisplay;
       {
           std::unique_lock<std::mutex> lock(m_screenMutex);
           m_screenChanged.wait(lock, [this] {
               return !m_displayUpdateRunning || m_pendingUpdate;
           });

           if (!m_displayUpdateRunning) break;
           
           screenToDisplay = m_currentScreen;
           m_pendingUpdate = false;
       } //release lock
       update(screenToDisplay);
       updateStatusBar();
    }
}
