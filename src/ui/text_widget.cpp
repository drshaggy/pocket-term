#include "text_widget.h"
#include "../drivers/display.h"

TextWidget::TextWidget(std::string text, bool isHighlighted)
    : m_text(text),
      m_isHighlighted(isHighlighted)
{}

void TextWidget::render(Display* display, const uint8_t& x, const uint8_t& y) const {
    display->drawText(m_text, x, y, m_isHighlighted);
}

std::unique_ptr<Widget> TextWidget::clone() {
    return std::make_unique<TextWidget>(m_text, m_isHighlighted);
}
