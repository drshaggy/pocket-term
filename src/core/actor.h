#ifndef ACTOR_H_
#define ACTOR_H_

#include "message.h"

#include <queue>
#include <thread>
#include <atomic>
#include <memory>
#include <map>
#include <mutex>

class Enqueuer
{
private:
    std::queue<Message>& m_queue;
    std::mutex& m_mutex;
public:
    Enqueuer(std::queue<Message>& queue, std::mutex& mutex)
        : m_queue(queue), m_mutex(mutex) {}
    Enqueuer(const Enqueuer& other)
        : m_queue(other.m_queue), m_mutex(other.m_mutex) {}
    void enqueue(Message message) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(std::move(message));
    }
};

class Actor
{
    template<typename ActorType>
    friend std::unique_ptr<ActorType> launchRootActor();
private:
    //ID
    size_t m_actorId;
    Actor* m_parent;
    static std::atomic<size_t> s_nextActorId;
    //Nested 
    std::map<size_t, std::unique_ptr<Actor>> m_nestedActors;
    //Thread
    std::atomic<bool> m_running;
    std::thread m_actorThread;
    //Queue
    std::queue<Message> m_messageQueue;
    std::mutex m_queueMutex;
    Enqueuer m_selfEnqueuer;
    Enqueuer m_callerEnqueuer;
    
    void actor();
    virtual void setUp() {}
    virtual void cleanUp() {}
    virtual void handleMessage(Message& message);
    void actorCore();
protected:
    void launchActor();
    void launchActorUnthreaded();
    virtual void doActorCore();
    std::optional<Message> dequeue();
    void sendMessageToCaller(Message& message);
    
    template<typename ActorType, typename... Args>
    Enqueuer launchNestedActor(Actor& caller, Args&&... args) {
        auto nested = std::make_unique<ActorType>(caller, std::forward<Args>(args)...);
        size_t nestedId = nested->getActorId();

        nested->launchActor();

        m_nestedActors[nestedId] = std::move(nested);
        return m_nestedActors[nestedId]->getSelfEnqueuer();
    }
public:
    Actor();
    Actor(Actor& parent);
    ~Actor();
    size_t getActorId() {return m_actorId;};
    Enqueuer& getSelfEnqueuer() {return m_selfEnqueuer;};
    Enqueuer& getCallerEnqueuer() {return m_callerEnqueuer;};
    void enqueue(Message message);
};

void sendMessage(Enqueuer enqueuer, Message& message);

template<typename ActorType>
std::unique_ptr<ActorType> launchRootActor() {
    auto actor = std::make_unique<ActorType>();
    //bypass threading for root actor
    actor->launchActorUnthreaded();
    return actor;
}


#endif // ACTOR_H_
