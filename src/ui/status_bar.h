#ifndef STATUS_BAR_H_
#define STATUS_BAR_H_

#include "time_widget.h"

class Display;

class StatusBar
{
private:
	uint8_t m_width;
	uint8_t m_height;
	std::unique_ptr<TimeWidget> m_timeWidget;
public:
	StatusBar() = default;
	StatusBar(uint8_t width, uint8_t height);
	void setTimeWidget(std::unique_ptr<TimeWidget>& widget) {m_timeWidget = std::move(widget);}
	void render(Display* display);
	void updateTime();
};

#endif // STATUS_BAR_H_
