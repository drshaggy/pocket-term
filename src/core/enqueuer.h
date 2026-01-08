#ifndef ENQUEUER_H_
#define ENQUEUER_H_

#include <queue>
#include <mutex>
#include <string>

class Message;

class Enqueuer
{
private:
    size_t* m_id;
    std::queue<Message>* m_queue;
    std::mutex* m_mutex;
    std::string m_name;
public:
    Enqueuer() = default;
    Enqueuer& operator=(const Enqueuer& other);
    Enqueuer(Enqueuer&& other) noexcept = default;
    Enqueuer& operator=(Enqueuer&& other) noexcept = default;
    ~Enqueuer() = default;

    Enqueuer(std::queue<Message>& queue, std::mutex& mutex, size_t& id, std::string m_name);
    Enqueuer(const Enqueuer& other);
    void enqueue(Message message);
    bool isEqual(Enqueuer other);
    std::string getName() const { return m_name; }
};

#endif // ENQUEUER_H_
