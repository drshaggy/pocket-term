#ifndef STATUS_BAR_H_
#define STATUS_BAR_H_

#include "widget.h"

class Display;

class StatusBar
{
private:
	uint8_t m_width;
	uint8_t m_height;
	std::unique_ptr<Widget> m_rootWidget;
public:
	StatusBar() = default;
	StatusBar(uint8_t width, uint8_t height);
	void setRootWidget(std::unique_ptr<Widget> widget) {m_rootWidget = std::move(widget);}
	void render(Display* display);
};

#endif // STATUS_BAR_H_
