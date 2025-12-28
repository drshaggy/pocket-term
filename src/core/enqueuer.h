#ifndef ENQUEUER_H_
#define ENQUEUER_H_

#include <queue>
#include <mutex>

class Message;

class Enqueuer
{
private:
    std::queue<Message>* m_queue;
    std::mutex* m_mutex;
public:
    Enqueuer() = default;
    Enqueuer(std::queue<Message>& queue, std::mutex& mutex);
    Enqueuer(const Enqueuer& other);
    void enqueue(Message message);
};

#endif // ENQUEUER_H_
