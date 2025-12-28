#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "enqueuer.h"
#include "../ui/screen.h"

#include <cstdint>
#include <memory>


enum MessageType {
	KEY_PRESS,
	TICK,
 ACKNOWLEDGE,
 SCREEN,
 SUBSCRIBE
};

class MessageData {
protected:
    MessageData() = default;
    MessageData(MessageType messageType) : m_messageType(messageType) {}
    MessageType m_messageType;
public:
    virtual ~MessageData() = default;
    MessageType getMessageType() {return m_messageType;}
};

class KeyMessageData : public MessageData {
private:
    char m_key;
    [[maybe_unused]]uint32_t m_timestamp;
public:
    KeyMessageData(char key, uint32_t ts)
        : MessageData(KEY_PRESS),
          m_key(key),
          m_timestamp(ts) {}
    char getKey() {return m_key;}
};

class AcknowledgeMessageData : public MessageData {
private:
    bool m_success;
public:
    AcknowledgeMessageData(bool success) : MessageData(ACKNOWLEDGE), m_success(success) {}
    bool isSuccess() {return m_success;}
};

class ScreenMessageData : public MessageData {
private:
    Screen m_screen;
public:
    ScreenMessageData(Screen& screen) : MessageData(SCREEN), m_screen(screen) {}
    Screen getScreen() {return m_screen;}
};

class SubscribeMessageData : public MessageData {
private:
    MessageType m_messageType;
    Enqueuer m_enqueuer;
public:
    SubscribeMessageData(MessageType m, Enqueuer e);
    Enqueuer getEnqueuer();
    MessageType getMessageType() {return m_messageType;}
};
    

class Message {
public:
    MessageType type;
    std::unique_ptr<MessageData> data;
    Message() = default;
    Message(Message&&) = default;
    Message& operator=(Message&&) = default;
    Message(const Message&) = delete;
    Message& operator=(const Message&) = delete;
};

template <typename TMessageData, typename... Args>
static Message createMessage(Args&&... args) {
    Message m;
    m.data = std::make_unique<TMessageData>(std::forward<Args>(args)...);
    m.type = m.data->getMessageType();
    return m;
}

#endif // MESSAGE_H_
