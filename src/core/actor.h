#ifndef ACTOR_H_
#define ACTOR_H_

#include "enqueuer.h"
#include "message.h"
#include "logging.h"

#include <spdlog/spdlog.h>
#include <queue>
#include <thread>
#include <atomic>
#include <memory>
#include <map>
#include <mutex>


class Subscription
{
private:
    MessageType m_messageType;
    std::vector<Enqueuer> m_subscribers;
    std::shared_ptr<spdlog::logger> m_logger;
public:
    Subscription() : m_logger(createLogger("subscription")) {}
    Subscription(MessageType messageType) : m_messageType(messageType), m_logger(createLogger("subscription")) {}
    MessageType getMessageType() {return m_messageType;}
    const std::vector<Enqueuer>& getSubscribers() const {return m_subscribers;}
    void add(Enqueuer enqueuer) {m_subscribers.push_back(enqueuer);}
    void remove(Enqueuer enqueuer);
};

class Actor
{
    template<typename ActorType>
    friend std::unique_ptr<ActorType> launchRootActor();
private:
    //ID
    size_t m_actorId;
    Actor* m_caller;
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
    std::vector<Enqueuer> m_nestedEnqueuers;
    std::map<MessageType, Subscription> m_subscriptions;
    
    void actor();
    virtual void setUp() {}
    virtual void cleanUp() {}
    void actorCore();
    void addToSubs(MessageType messageType, Enqueuer enqueuer);
    void removeFromSubs(Enqueuer enqueuer);
protected:
    const std::string m_actorName;
    std::shared_ptr<spdlog::logger> m_logger;
    void initLogger(const std::string& name);
    virtual void handleMessage(Message& message);
    void subscribe(MessageType messageType) {


        Message m = createMessage<SubscribeMessageData>(messageType, m_selfEnqueuer);
        sendMessageToCaller(m);
    }
    void unsubscribeAll() {
        Message m = createMessage<UnsubscribeMessageData>(m_selfEnqueuer);
        sendMessageToCaller(m);
    }
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
        m_nestedEnqueuers.push_back(m_nestedActors[nestedId]->getSelfEnqueuer());
        return m_nestedActors[nestedId]->getSelfEnqueuer();
    }
public:
    Actor(const std::string actorName);
    Actor(Actor& caller, const std::string actorName);
    ~Actor();
    size_t getActorId() {return m_actorId;};
    Enqueuer& getSelfEnqueuer() {return m_selfEnqueuer;};
    Enqueuer& getCallerEnqueuer() {return m_callerEnqueuer;};
    void enqueue(Message message);
};

void sendMessage(Enqueuer enqueuer, const Message& message);

template<typename ActorType>
std::unique_ptr<ActorType> launchRootActor() {
    auto actor = std::make_unique<ActorType>();
    //bypass threading for root actor
    actor->launchActorUnthreaded();
    return actor;
}


#endif // ACTOR_H_
