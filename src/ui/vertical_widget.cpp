#include "vertical_widget.h"
#include "../config.h"

void VerticalWidget::render(Display* display, const uint8_t& x, const uint8_t& y ) const {
    uint8_t lx {x};
    uint8_t ly {y};
    for (const auto& widget : m_widgets) {
        widget->render(display, lx, ly);
        ly += SEGMENT_WIDTH;
    }
}

std::unique_ptr<Widget> VerticalWidget::clone() {
    return std::make_unique<VerticalWidget>();
}

void VerticalWidget::add(std::unique_ptr<Widget>& widget) {
   m_widgets.push_back(std::move(widget)); 
}
