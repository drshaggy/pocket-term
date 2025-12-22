#include "actor.h"

#include <spdlog/spdlog.h>

Actor::Actor()
    : m_running { false }
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
    m_running = true;
    m_actorThread = std::thread(&Actor::actorLoop, this); 
}

void Actor::actorLoop() {
    while( m_running ) {
        actorCore();
    }
}

void Actor::actorCore() {
   // abstract 
}
