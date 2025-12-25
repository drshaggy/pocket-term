#ifndef UI_H_
#define UI_H_

#include "../drivers/display.h"
#include "../core/actor.h"

#include <string>
#include <memory>

class UI : public Actor
{
private:
    std::unique_ptr<Display> m_display;
    Screen m_currentScreen;
protected:
    virtual void doActorCore() override;
    virtual void handleMessage(Message& message) override;
public:
    UI();
    UI(Actor& caller);
    virtual ~UI() = default;
    void print(const std::string& text);
    void printHighlighted(const std::string& text);
    void println(const std::string& text);
    void clear();
    void update();
};

#endif // UI_H_
