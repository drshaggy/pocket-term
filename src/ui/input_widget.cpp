#include "input_widget.h"
#include "../drivers/display.h"

InputWidget::InputWidget(std::string defaultText, bool isSelected)
    : m_text(defaultText),
      m_isSelected(isSelected)
{}

void InputWidget::render(Display* display, const uint16_t& x, const uint16_t& y) const {
   display->drawText(m_text, x, y); 
}

std::unique_ptr<Widget> InputWidget::clone() {
    return std::make_unique<InputWidget>(m_text, m_isSelected);
}
