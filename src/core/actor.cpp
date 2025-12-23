#include "actor.h"

#include <spdlog/spdlog.h>

std::atomic<size_t> Actor::s_nextActorId{1};

Actor::Actor()
    : m_actorId(s_nextActorId.fetch_add(1)),
      m_running { false }
{
    
}

Actor::~Actor()
{
    m_running = false;

    if (m_actorThread.joinable()) {
        m_actorThread.join();
    }
}


void Actor::startActorLoop() {
    if (!m_running) {
        m_running = true;
        m_actorThread = std::thread(&Actor::actorLoop, this); 
    }
}

void Actor::actorLoop() {
    while( m_running ) {
        auto msg = dequeue();
        if (msg) {
            handleMessage(*msg);
        }
        actorCore();
    }
}

std::optional<Message> Actor::dequeue() {
    std::lock_guard<std::mutex> lock(m_queueMutex);
    if (m_messageQueue.empty()) {
        return std::nullopt;
    }
    Message m = std::move(m_messageQueue.front());
    m_messageQueue.pop();
    return m;
}

void Actor::actorCore() {
   // abstract 
}

void Actor::sendMessageToParent(Message& message) {
    m_parent->enqueue(std::move(message));
}

void Actor::enqueue(Message message) {
    m_messageQueue.push(std::move(message));
}

void Actor::handleMessage([[maybe_unused]]Message& message) {
    
}
