#ifndef TEXT_WIDGET_H_
#define TEXT_WIDGET_H_

#include "widget.h"

#include <string>

class TextWidget : public Widget
{
private:
    std::string m_text;
    bool m_isHighlighted;
public:
    TextWidget(std::string text, bool isHighlighted);
    std::string getText() {return m_text;}
    virtual void render(Display* display, const uint16_t& x, const uint16_t& y) const override;
    virtual std::unique_ptr<Widget> clone() override;
};

#endif // TEXT_WIDGET_H_
