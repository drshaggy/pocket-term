#ifndef EVENT_H_
#define EVENT_H_

#include <cstdint>
#include <memory>

enum EventType {
	KEY_PRESS,
	TICK,
};

class EventData {
protected:
    EventData() = default;
public:
    virtual ~EventData() = default;
};

class KeyEventData : public EventData {
private:
    char m_key;
    [[maybe_unused]]uint32_t m_timestamp;
public:
    KeyEventData(char key, uint32_t ts) : m_key(key), m_timestamp(ts) {}
    char getKey() {return m_key;}
};

struct Event {
    EventType type;
    std::unique_ptr<EventData> data;
    static Event createKeyEvent(char key, uint32_t ts);

    Event() = default;
    Event(Event&&) = default;
    Event& operator=(Event&&) = default;
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
};


#endif // EVENT_H_
