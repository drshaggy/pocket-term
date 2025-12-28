#ifndef VERTICAL_WIDGET_H_
#define VERTICAL_WIDGET_H_

#include "widget.h"

#include <vector>

class VerticalWidget : public Widget
{
private:
	std::vector<std::unique_ptr<Widget>> m_widgets;
public:
	virtual void render(Display* display, const uint8_t& x, const uint8_t& y) const override;
	virtual std::unique_ptr<Widget> clone() override;
	void add(std::unique_ptr<Widget>& widget);
};


#endif // VERTICAL_WIDGET_H_
