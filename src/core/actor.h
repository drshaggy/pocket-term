#ifndef ACTOR_H_
#define ACTOR_H_

#include <queue>
#include <thread>
#include <atomic>
#include <memory>

class Message {};

class Actor
{
    template<typename ActorType>
    friend std::unique_ptr<ActorType> launchActor();
private:
    std::thread m_actorThread;
    void actorLoop();
protected:
    std::atomic<bool> m_running;
    std::queue<Message> m_messageQueue;
    void startActorLoop();
    virtual void actorCore();
public:
    Actor();
    ~Actor();
};

template<typename ActorType>
std::unique_ptr<ActorType> launchActor() {
    auto actor = std::make_unique<ActorType>();
    actor->startActorLoop();
    return actor;
}

#endif // ACTOR_H_
