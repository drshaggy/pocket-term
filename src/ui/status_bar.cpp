#include "status_bar.h"
#include "../config.h"

StatusBar::StatusBar(uint16_t width, uint16_t height)
    : m_width(width),
      m_height(height),
      m_titleWidget(std::make_unique<TextWidget>("Pocket Term", true)),
      m_timeWidget(std::make_unique<TimeWidget>(true)),
      m_boxWidget(std::make_unique<BoxWidget>(SCREEN_WIDTH, SEGMENT_HEIGHT))
{}


void StatusBar::render(Display* display) { 
    if (m_boxWidget) {
        m_boxWidget->render(display, 0, 0);
    }
    if (m_titleWidget) {
        m_titleWidget->render(display, 0, 0);
    }
    if (m_timeWidget) {
        m_timeWidget->render(display, 700, 0);
    }
}
