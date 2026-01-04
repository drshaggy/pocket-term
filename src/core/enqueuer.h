#ifndef ENQUEUER_H_
#define ENQUEUER_H_

#include <queue>
#include <mutex>

class Message;

class Enqueuer
{
private:
    size_t* m_id;
    std::queue<Message>* m_queue;
    std::mutex* m_mutex;
public:
    Enqueuer() = default;
    Enqueuer& operator=(const Enqueuer& other);
    Enqueuer(Enqueuer&& other) noexcept = default;
    Enqueuer& operator=(Enqueuer&& other) noexcept = default;
    ~Enqueuer() = default;

    Enqueuer(std::queue<Message>& queue, std::mutex& mutex, size_t& id);
    Enqueuer(const Enqueuer& other);
    void enqueue(Message message);
    bool isEqual(Enqueuer other);
};

#endif // ENQUEUER_H_
