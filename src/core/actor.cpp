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
        actorCore();
    }
}

void Actor::actorCore() {
   // abstract 
}
