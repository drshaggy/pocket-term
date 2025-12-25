#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../ui/screen.h"

#include <cstdint>
#include <memory>

enum MessageType {
	KEY_PRESS,
	TICK,
 ACKNOWLEDGE,
 SCREEN
};

class MessageData {
protected:
    MessageData() = default;
public:
    virtual ~MessageData() = default;
};

class KeyMessageData : public MessageData {
private:
    char m_key;
    [[maybe_unused]]uint32_t m_timestamp;
public:
    KeyMessageData(char key, uint32_t ts) : m_key(key), m_timestamp(ts) {}
    char getKey() {return m_key;}
};

class AcknowledgeMessageData : public MessageData {
private:
    bool m_success;
public:
    AcknowledgeMessageData(bool success) : m_success(success) {}
    bool isSuccess() {return m_success;}
};

class ScreenMessageData : public MessageData {
private:
    Screen m_screen;
public:
    ScreenMessageData(Screen screen) : m_screen(screen) {}
    Screen getScreen() {return m_screen;}
};

struct Message {
    MessageType type;
    std::unique_ptr<MessageData> data;
    static Message createKeyMessage(char key, uint32_t ts);
    static Message createAckMessage(bool success);
    static Message createScreenMessage(Screen screen);

    Message() = default;
    Message(Message&&) = default;
    Message& operator=(Message&&) = default;
    Message(const Message&) = delete;
    Message& operator=(const Message&) = delete;
};


#endif // MESSAGE_H_
