#include "message_source.h"

bool MessageSource::hasMessages() {
    return !m_messageQueue.empty();
}

Message MessageSource::getNextMessage(){
    //move as MessageData is unique_ptr
    Message e = std::move(m_messageQueue.front());
    m_messageQueue.pop();
    return e;
}

void MessageSource::poll() {}
