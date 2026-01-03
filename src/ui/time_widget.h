#ifndef TIME_WIDGET_H_
#define TIME_WIDGET_H_

#include "widget.h"
#include <string>

class TimeWidget : public Widget
{
private:
	std::string m_time;
	bool m_isHighlighted;
public:
	TimeWidget(bool isHighlighted = false);
	std::string getText() const {return m_time;}
	virtual void render(Display* display, const uint8_t& x, const uint8_t& y) const override;
	virtual std::unique_ptr<Widget> clone() override;
	void updateTime();
};


#endif // TIME_WIDGET_H_
