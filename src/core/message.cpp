#include "message.h"
#include "enqueuer.h"

SubscribeMessageData::SubscribeMessageData(MessageType m, Enqueuer e)
    : MessageData(SUBSCRIBE),
      m_messageType(m),
      m_enqueuer(e)
{}

Enqueuer SubscribeMessageData::getEnqueuer() {
    return m_enqueuer;
}
