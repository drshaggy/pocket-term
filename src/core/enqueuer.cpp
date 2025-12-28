#include "enqueuer.h"
#include "message.h"


Enqueuer::Enqueuer(std::queue<Message>& queue, std::mutex& mutex)
    : m_queue(&queue), m_mutex(&mutex) {}

Enqueuer::Enqueuer(const Enqueuer& other)
    : m_queue(other.m_queue), m_mutex(other.m_mutex) {}

void Enqueuer::enqueue(Message message) {
    std::lock_guard<std::mutex> lock(*m_mutex);
    m_queue->push(std::move(message));
}
