#ifndef MESSAGE_SOURCE_H_
#define MESSAGE_SOURCE_H_

#include "../core/message.h"
#include <queue>


class MessageSource {
protected:
	std::queue<Message> m_messageQueue;
public:
	virtual ~MessageSource() = default;
	bool hasMessages();
	Message getNextMessage();
	virtual void poll();
};

#endif // MESSAGE_SOURCE_H_
