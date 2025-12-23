#ifndef ACTOR_H_
#define ACTOR_H_

#include "message.h"

#include <queue>
#include <thread>
#include <atomic>
#include <memory>
#include <map>


class Actor
{
    template<typename ActorType>
    friend std::unique_ptr<ActorType> launchActor();
private:
    size_t m_actorId;
    Actor* m_parent;
    static std::atomic<size_t> s_nextActorId;
    std::thread m_actorThread;
    std::map<size_t, std::unique_ptr<Actor>> m_nestedActors;
    std::queue<Message> m_messageQueue;
    std::mutex m_queueMutex;
    void actorLoop();
protected:
    std::atomic<bool> m_running;
    
    std::optional<Message> dequeue();
    virtual void handleMessage(Message& message);
    virtual void actorCore();
    void setParent(Actor* actor) {m_parent = actor;}
    
    template<typename ActorType, typename... Args>
    size_t launchNestedActor(Args&&... args) {
        auto nested = std::make_unique<ActorType>(std::forward<Args>(args)...);
        nested->setParent(this);
        size_t nestedId = nested->getActorId();

        nested->startActorLoop();

        m_nestedActors[nestedId] = std::move(nested);
        return nestedId;
    }
    
    void sendMessageToParent(Message& message);
    void sendMessageToChild(size_t actorId, Message& message);
public:
    Actor();
    ~Actor();
    void startActorLoop();
    size_t getActorId() {return m_actorId;};
    void enqueue(Message message);
};

template<typename ActorType>
std::unique_ptr<ActorType> launchActor() {
    auto actor = std::make_unique<ActorType>();
    actor->startActorLoop();
    return actor;
}

#endif // ACTOR_H_
