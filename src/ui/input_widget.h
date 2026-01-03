#ifndef INPUT_WIDGET_H_
#define INPUT_WIDGET_H_

#include "widget.h"

#include <string>

class InputWidget : public Widget
{
private:
	std::string m_text;
	bool m_isSelected;
public:
	InputWidget(std::string defaultText, bool isSelected);
	std::string getText() const {return m_text;}
	virtual void render(Display* display, const uint8_t& x, const uint8_t& y) const override;
	virtual std::unique_ptr<Widget> clone() override;
};

#endif // INPUT_WIDGET_H_
