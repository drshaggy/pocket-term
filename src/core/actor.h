#ifndef ACTOR_H_
#define ACTOR_H_

#include <queue>
#include <thread>
#include <atomic>
#include <memory>
#include <map>

class Message {};

class Actor
{
    template<typename ActorType>
    friend std::unique_ptr<ActorType> launchActor();
private:
    size_t m_actorId;
    static std::atomic<size_t> s_nextActorId;
    std::thread m_actorThread;
    std::map<size_t, std::unique_ptr<Actor>> m_nestedActors;
    void actorLoop();
protected:
    std::atomic<bool> m_running;
    std::queue<Message> m_messageQueue;
    virtual void actorCore();
    template<typename ActorType, typename... Args>
    size_t launchNestedActor(Args&&... args) {
        auto nested = std::make_unique<ActorType>(std::forward<Args>(args)...);
        size_t nestedId = nested->getActorId();

        nested->startActorLoop();

        m_nestedActors[nestedId] = std::move(nested);
        return nestedId;
    }
public:
    Actor();
    ~Actor();
    void startActorLoop();
    size_t getActorId() {return m_actorId;};
};

template<typename ActorType>
std::unique_ptr<ActorType> launchActor() {
    auto actor = std::make_unique<ActorType>();
    actor->startActorLoop();
    return actor;
}

#endif // ACTOR_H_
