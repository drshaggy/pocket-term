#include "status_bar.h"
#include "text_widget.h"
#include "time_widget.h"

StatusBar::StatusBar(uint8_t width, uint8_t height)
    : m_width(width), m_height(height)
{
    std::unique_ptr<Widget> text = std::make_unique<TextWidget>("STATUS BAR", true);
    std::unique_ptr<TimeWidget> time = std::make_unique<TimeWidget>(true);
    setTimeWidget(time);
};


void StatusBar::render(Display* display) { 
    if (m_timeWidget) {
        m_timeWidget->render(display, 0, 0);
    }
}

void StatusBar::renderTime(Display* display) {
    if (m_timeWidget) {
        m_timeWidget->updateTime(); 
        m_timeWidget->render(display, 0, 0);
    }
}
