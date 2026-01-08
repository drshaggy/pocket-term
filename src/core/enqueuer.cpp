#include "enqueuer.h"
#include "message.h"


Enqueuer::Enqueuer(std::queue<Message>& queue, std::mutex& mutex, size_t& id, std::string name)
    : m_id(&id), m_queue(&queue), m_mutex(&mutex), m_name(name)  {}

Enqueuer::Enqueuer(const Enqueuer& other)
    : m_id(other.m_id), m_queue(other.m_queue), m_mutex(other.m_mutex), m_name(other.m_name) {}

Enqueuer& Enqueuer::operator=(const Enqueuer& other) {
    if (this!= &other) {
        m_id = other.m_id;
        m_queue = other.m_queue;
        m_mutex = other.m_mutex;
        m_name = other.m_name;
    }
    return *this;
}

void Enqueuer::enqueue(Message message) {
    std::lock_guard<std::mutex> lock(*m_mutex);
    m_queue->push(std::move(message));
}

bool Enqueuer::isEqual(Enqueuer other) {
    return m_id == other.m_id;
}
