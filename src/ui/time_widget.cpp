#include "time_widget.h"
#include "../drivers/display.h"

#include <chrono>
#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

TimeWidget::TimeWidget(bool isHighlighted)
    : m_isHighlighted(isHighlighted)
{
    updateTime();
    m_running = true;
    m_updateThread = std::thread(&TimeWidget::updateThreadLoop, this);
}

TimeWidget::~TimeWidget()
{
    m_running = false;

    if(m_updateThread.joinable()) {
        m_updateThread.join();
    }
}

void TimeWidget::render(Display* display, const uint16_t& x, const uint16_t& y) const {
    std::string timeCopy;
    {
        std::lock_guard<std::mutex> lock(m_timeMutex);
        timeCopy = m_time;
    }
    display->drawText(timeCopy, x, y, m_isHighlighted); 
}

std::unique_ptr<Widget> TimeWidget::clone() {
    return std::make_unique<TimeWidget>(m_isHighlighted);
}

void TimeWidget::updateTime() {
    auto now = std::chrono::system_clock::now();
    std::lock_guard<std::mutex> lock(m_timeMutex);
    m_time = std::format("{:%H:%M}", now);
}

void TimeWidget::updateThreadLoop() {
    while (m_running) {
        updateTime();
        for (int i = 0; i < 1 && m_running; ++i) {
            std::this_thread::sleep_for(1000ms);
        }
    } 
}
