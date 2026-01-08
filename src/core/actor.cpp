#include "actor.h"
#include "logging.h"

#include <vector>

std::atomic<size_t> Actor::s_nextActorId{1};

Actor::Actor(const std::string actorName)
    : m_actorId(s_nextActorId.fetch_add(1)),
      m_running { false },
      m_selfEnqueuer(m_messageQueue, m_queueMutex, m_actorId),
      m_callerEnqueuer(m_messageQueue, m_queueMutex, m_actorId), //use own queuer for paerent as root.
      m_actorName(actorName),
      m_logger(createLogger(actorName))
{}


Actor::Actor(Actor& caller, const std::string actorName)
    : m_actorId(s_nextActorId.fetch_add(1)),
      m_running { false },
      m_selfEnqueuer(m_messageQueue, m_queueMutex, m_actorId),
      m_callerEnqueuer(caller.getSelfEnqueuer()),
      m_actorName(actorName),
      m_logger(createLogger(actorName))
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
    std::lock_guard<std::mutex> lock(m_queueMutex);
    m_messageQueue.push(std::move(message));
}

void Actor::handleMessage(Message& message) {
    // handles specific messages
    switch (message.type) {
        case SUBSCRIBE: {
            SubscribeMessageData data = static_cast<SubscribeMessageData&>(*message.data); 
            MessageType t = data.getMessageType();
            Enqueuer e = data.getEnqueuer();
            addToSubs(t, e);
            m_logger->debug("{} Subscribed to {}", m_actorName, MessageTypeNames[t]);
            break;
        }
        case CLOSE: {
            m_logger->info("Stopping {} Actor", m_actorName);
            for (const auto& enqueuer : m_nestedEnqueuers) {
                sendMessage(enqueuer, message);
            }
            m_running = false;
            break; 
        }
        case UNSUBSCRIBE: {
            UnsubscribeMessageData data = static_cast<UnsubscribeMessageData&>(*message.data); 
            Enqueuer e = data.getEnqueuer();
            removeFromSubs(e);
            break;
        }
            
        default:
            break;
    }
    

    //handles routing to children 
    for (const auto& [messageType, subscription] : m_subscriptions) {
        if (message.type == messageType) {
            m_logger->debug("Sending message type {} to {} nested actors",
                static_cast<int>(messageType), subscription.getSubscribers().size());
            for (const auto& enqueuer : subscription.getSubscribers()) {
                sendMessage(enqueuer, message);
                m_logger->debug("Sending {} message to child", static_cast<int>(messageType));
            }
        } 
    }
    
}

void Actor::addToSubs(MessageType messageType, Enqueuer enqueuer) {
    if (!m_subscriptions.contains(messageType)) {
        m_subscriptions[messageType] = Subscription(messageType);
    }
    m_subscriptions[messageType].add(enqueuer); 
}

void Actor::removeFromSubs(Enqueuer enqueuer) {
    for (auto& subscription : m_subscriptions) {
        m_logger->debug("Calling remove subscription");
        subscription.second.remove(enqueuer);
    }
}

void sendMessage(Enqueuer e, const Message& m) {
    Message copy = m;
    e.enqueue(copy);
}

void Subscription::remove(Enqueuer enqueuer) {
    std::erase_if(
        m_subscribers,
        [&enqueuer](const Enqueuer& subscriber) {return enqueuer.isEqual(subscriber);}
    );
}
