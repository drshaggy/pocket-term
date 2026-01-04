#include "actor.h"
#include "logging.h"

std::atomic<size_t> Actor::s_nextActorId{1};

Actor::Actor(const std::string actorName)
    : m_actorId(s_nextActorId.fetch_add(1)),
      m_running { false },
      m_selfEnqueuer(m_messageQueue, m_queueMutex),
      m_callerEnqueuer(m_messageQueue, m_queueMutex), //use own queuer for paerent as root.
      m_actorName(actorName),
      m_logger(createLogger(actorName))
{}


Actor::Actor(Actor& caller, const std::string actorName)
    : m_actorId(s_nextActorId.fetch_add(1)),
      m_running { false },
      m_selfEnqueuer(m_messageQueue, m_queueMutex),
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
    m_logger->debug("Actor handleMessage Called");
    if (message.type == SUBSCRIBE) {
        SubscribeMessageData data = static_cast<SubscribeMessageData&>(*message.data); 
        MessageType t = data.getMessageType();
        Enqueuer e = data.getEnqueuer();
        addToSubs(t, e);
        m_logger->debug("{} Subscribed to something", m_actorName);
    }
    for (const auto& [messageType, subscription] : m_subscriptions) {
        if (message.type == messageType) {
            for (const auto& enqueuer : subscription.getSubscribers()) {
                sendMessage(enqueuer, message);
                m_logger->debug("Sending {} message to child", static_cast<int>(messageType));
                return;
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


void sendMessage(Enqueuer e, const Message& m) {
    Message copy = m;
    e.enqueue(copy);
}

