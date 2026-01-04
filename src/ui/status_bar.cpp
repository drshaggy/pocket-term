#include "status_bar.h"
#include "../config.h"

StatusBar::StatusBar(uint16_t width, uint16_t height)
    : m_width(width),
      m_height(height),
      m_titleWidget(std::make_unique<TextWidget>("Pocket Term", true)),
      m_boxWidget(std::make_unique<BoxWidget>(SEGMENT_WIDTH * 10, SEGMENT_HEIGHT)),
      m_timeWidget(std::make_unique<TimeWidget>(true))
{}


void StatusBar::render(Display* display) { 
    if (m_titleWidget) {
        m_titleWidget->render(display, 0, 0);
    }
    if (m_boxWidget) {
        uint16_t length = m_titleWidget->getText().size();
        m_boxWidget->render(display, uint16_t(length * SEGMENT_WIDTH), 0);
    }
    if (m_timeWidget) {
        m_timeWidget->render(display, 400, 0);
    }
}
