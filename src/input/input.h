#ifndef INPUT_H_
#define INPUT_H_

#include "../core/actor.h"
#include "../drivers/keyboard.h"

class Input : public Actor
{
private:
    std::unique_ptr<Keyboard> m_keyboard;
protected:
    virtual void doActorCore() override;
    virtual void handleMessage(Message& message) override;
public:
    Input(Actor& caller);
    virtual ~Input() = default;
};

#endif // INPUT_H_
