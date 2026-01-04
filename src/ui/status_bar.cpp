#include "status_bar.h"
#include "../config.h"

StatusBar::StatusBar(uint8_t width, uint8_t height)
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
        m_boxWidget->render(display, uint8_t(40), 0);
    }
    if (m_timeWidget) {
        m_timeWidget->render(display, uint8_t(400), 0);
    }
}
