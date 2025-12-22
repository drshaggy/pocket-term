#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <cstdint>
#include <memory>

enum MessageType {
	KEY_PRESS,
	TICK,
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

struct Message {
    MessageType type;
    std::unique_ptr<MessageData> data;
    static Message createKeyMessage(char key, uint32_t ts);

    Message() = default;
    Message(Message&&) = default;
    Message& operator=(Message&&) = default;
    Message(const Message&) = delete;
    Message& operator=(const Message&) = delete;
};


#endif // MESSAGE_H_
