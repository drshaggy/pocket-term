#ifndef TIME_WIDGET_H_
#define TIME_WIDGET_H_

#include "widget.h"
#include <string>
#include <mutex>
#include <thread>
#include <atomic>


class TimeWidget : public Widget
{
private:
	Display* m_display;
	std::string m_time;
	mutable std::mutex m_timeMutex;
	std::thread m_updateThread;
	std::atomic<bool> m_running{false};
	bool m_isHighlighted;
public:
	TimeWidget(bool isHighlighted = false);
	~TimeWidget();
	void registerDisplay(Display* display) {m_display = display;}
	virtual void render(Display* display, const uint8_t& x, const uint8_t& y) const override;
	virtual std::unique_ptr<Widget> clone() override;
	void updateTime();
	void updateThreadLoop();
};


#endif // TIME_WIDGET_H_
