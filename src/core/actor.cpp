#include "actor.h"

#include <spdlog/spdlog.h>

std::atomic<size_t> Actor::s_nextActorId{1};

Actor::Actor()
    : m_actorId(s_nextActorId.fetch_add(1)),
      m_running { false },
      m_selfEnqueuer(m_messageQueue, m_queueMutex),
      m_callerEnqueuer(m_messageQueue, m_queueMutex) //use own queuer for paerent as root. 
{}

Actor::Actor(Actor& parent)
    : m_actorId(s_nextActorId.fetch_add(1)),
      m_running { false },
      m_selfEnqueuer(m_messageQueue, m_queueMutex),
      m_callerEnqueuer(parent.getSelfEnqueuer())
{}

Actor::~Actor()
{
    m_running = false;

    if (m_actorThread.joinable()) {
        m_actorThread.join();
    }
}

void Actor::launchActorUnthreaded() {
    if (!m_running) {
        m_running = true;
        actor();
    }
}

void Actor::launchActor() {
    if (!m_running) {
        m_running = true;
        m_actorThread = std::thread(&Actor::actor, this); 
    }
}

void Actor::actor() {
    setUp();
    actorCore();
    cleanUp();
}

void Actor::actorCore() {
    while( m_running ) {
        auto msg = dequeue();
        if (msg) {
            handleMessage(*msg);
        }
        doActorCore();
    }
}

void Actor::doActorCore() {
    //abstract
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


void Actor::sendMessageToCaller(Message& message) {
    sendMessage(m_callerEnqueuer, message);
}


void Actor::enqueue(Message message) {
    m_messageQueue.push(std::move(message));
}

void Actor::handleMessage([[maybe_unused]]Message& message) {
    
}

void sendMessage(Enqueuer e, Message& m) {
    e.enqueue(std::move(m));
}
