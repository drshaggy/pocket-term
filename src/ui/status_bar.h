#ifndef STATUS_BAR_H_
#define STATUS_BAR_H_

#include "text_widget.h"
#include "time_widget.h"
#include "box_widget.h"

class Display;

class StatusBar
{
private:
	uint8_t m_width;
	uint8_t m_height;
	std::unique_ptr<TextWidget> m_titleWidget;
	std::unique_ptr<BoxWidget> m_boxWidget;
	std::unique_ptr<TimeWidget> m_timeWidget;
	Display* m_display;
public:
	StatusBar() = default;
	StatusBar(uint8_t width, uint8_t height);
	void render(Display* display);
};

#endif // STATUS_BAR_H_
