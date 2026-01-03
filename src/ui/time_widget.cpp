#include "time_widget.h"
#include "../drivers/display.h"

#include <chrono>

TimeWidget::TimeWidget(bool isHighlighted)
    : m_isHighlighted(isHighlighted)
{
    updateTime();
}


void TimeWidget::render(Display* display, const uint8_t& x, const uint8_t& y) const {
    display->drawText(m_time, x, y); 
}

std::unique_ptr<Widget> TimeWidget::clone() {
    return std::make_unique<TimeWidget>(m_isHighlighted);
}

void TimeWidget::updateTime() {
    auto now = std::chrono::system_clock::now();
    m_time = std::format("{:%H:%M}", now);
}
