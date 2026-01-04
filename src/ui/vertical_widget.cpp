#include "vertical_widget.h"
#include "../config.h"

void VerticalWidget::render(Display* display, const uint16_t& x, const uint16_t& y ) const {
    uint16_t lx {x};
    uint16_t ly {y};
    for (const auto& widget : m_widgets) {
        widget->render(display, lx, ly);
        ly += SEGMENT_WIDTH;
    }
}

std::unique_ptr<Widget> VerticalWidget::clone() {
    std::unique_ptr<VerticalWidget> clone = std::make_unique<VerticalWidget>();
    for (const auto& widget : m_widgets) {
        std::unique_ptr<Widget> cloned = widget->clone();
        clone->add(cloned);
    }
    return clone;
}

void VerticalWidget::add(std::unique_ptr<Widget>& widget) {
   m_widgets.push_back(std::move(widget)); 
}
