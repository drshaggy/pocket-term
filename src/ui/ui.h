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
public:
    UI();
    virtual ~UI() = default;
    void print(const std::string& text);
    void printHighlighted(const std::string& text);
    void println(const std::string& text);
    void clear();
    void update();
    virtual void actorCore() override;
};

#endif // UI_H_
