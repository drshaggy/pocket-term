#include "screen.h"
#include "../config.h"

Screen::Screen(uint16_t width, uint16_t height)
	: m_width{width}, m_height{height}
{};

Screen::Screen(const Screen& other)
    : m_width(other.m_width),
      m_height(other.m_height)
{
    if (other.m_rootWidget) {
        m_rootWidget = other.m_rootWidget->clone();
    }
}

Screen& Screen::operator=(const Screen& other) {
    if (this != &other) {
        m_width = other.m_width;
        m_height = other.m_height;

        if (other.m_rootWidget) {
            m_rootWidget = other.m_rootWidget->clone();
        } else {
            m_rootWidget.reset();
        }
    }
    return *this;
}

void Screen::render(Display* display) {
    if (m_rootWidget) {
        m_rootWidget->render(display, 0, SEGMENT_HEIGHT);
    }
}
