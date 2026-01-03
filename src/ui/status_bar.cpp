#include "status_bar.h"
#include "text_widget.h"

StatusBar::StatusBar(uint8_t width, uint8_t height)
    : m_width(width), m_height(height)
{
    std::unique_ptr<Widget> text = std::make_unique<TextWidget>("STATUS BAR", true);
    setRootWidget(text);
};


void StatusBar::render(Display* display) { 
    if (m_rootWidget) {
        m_rootWidget->render(display, 0, 0);
    }
}
