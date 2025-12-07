#ifndef EVENT_SOURCE_H_
#define EVENT_SOURCE_H_

#include "../event.h"
#include <queue>


class EventSource {
protected:
	std::queue<Event> m_eventQueue;
public:
	virtual ~EventSource() = default;
	bool hasEvents();
	Event getNextEvent();
	virtual void poll();
};

#endif // EVENT_SOURCE_H_
