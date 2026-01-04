#include "list_widget.h"
#include "../drivers/display.h"
#include "../config.h"

ListWidget::ListWidget(std::vector<std::string> items) : m_items(items) {}

void ListWidget::render(Display* display, const uint16_t& x, const uint16_t& y) const {
    uint16_t offset{0};
    uint8_t index{0};
    for (const auto& item : m_items) {
        display->drawText(item, x, y + offset, index == m_selectedItem);
        offset += SEGMENT_HEIGHT;
        index += 1;
    }
}

std::unique_ptr<Widget> ListWidget::clone() {
    return std::make_unique<ListWidget>(m_items);
}
