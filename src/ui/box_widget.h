#ifndef BOX_WIDGET_H_
#define BOX_WIDGET_H_

#include "widget.h"

class BoxWidget : public Widget
{
private:
	const uint8_t m_width;
	const uint8_t m_height;
	const bool m_hasBorder;
	const bool m_isFilled;
public:
	BoxWidget(const uint8_t width,
			  const uint8_t height,
			  const bool hasBorder = true,
			  const bool isFilled = false);
	virtual void render(Display* display, const uint8_t& x, const uint8_t& y) const override;
	virtual std::unique_ptr<Widget> clone() override;

};

#endif // BOX_WIDGET_H_
