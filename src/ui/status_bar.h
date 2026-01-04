#ifndef STATUS_BAR_H_
#define STATUS_BAR_H_

#include "text_widget.h"
#include "time_widget.h"
#include "box_widget.h"

class Display;

class StatusBar
{
private:
	uint16_t m_width;
	uint16_t m_height;
	std::unique_ptr<TextWidget> m_titleWidget;
	std::unique_ptr<TimeWidget> m_timeWidget;
	std::unique_ptr<BoxWidget> m_boxWidget;
	Display* m_display;
public:
	StatusBar() = default;
	StatusBar(uint16_t width, uint16_t height);
	void render(Display* display);
};

#endif // STATUS_BAR_H_
