#include "box_widget.h"
#include "../drivers/display.h"

BoxWidget::BoxWidget(const uint16_t width,
                     const uint16_t height,
                     const bool hasBorder,
                     const bool isFilled)
    : m_width(width),
      m_height(height),
      m_hasBorder(hasBorder),
      m_isFilled(isFilled)
{}

void BoxWidget::render(Display* display, const uint16_t& x, const uint16_t& y) const {
   display->drawBox(m_width, m_height, m_hasBorder, m_isFilled, x, y); 
}

std::unique_ptr<Widget> BoxWidget::clone() {
    return std::make_unique<BoxWidget>(m_width, m_height, m_hasBorder, m_isFilled);
}

