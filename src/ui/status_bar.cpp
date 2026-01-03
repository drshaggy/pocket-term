#include "status_bar.h"

StatusBar::StatusBar(uint8_t width, uint8_t height)
    : m_width(width), m_height(height)
{};

void StatusBar::render(Display* display) { 
    if (m_rootWidget) {
        m_rootWidget->render(display, 0, 0);
    }
}
