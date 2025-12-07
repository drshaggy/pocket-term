#include "event_source.h"

bool EventSource::hasEvents() {
    return !m_eventQueue.empty();
}

Event EventSource::getNextEvent(){
    //move as EventData is unique_ptr
    Event e = std::move(m_eventQueue.front());
    m_eventQueue.pop();
    return std::move(e);
}

void EventSource::poll() {}
