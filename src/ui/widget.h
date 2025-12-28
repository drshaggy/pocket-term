#ifndef WIDGET_H_
#define WIDGET_H_

#include <memory>

class Display;

class Widget
{
public:
    virtual ~Widget() = default;
    virtual void render([[maybe_unused]]Display* display) const = 0;
    virtual std::unique_ptr<Widget> clone() = 0;
};

#endif // WIDGET_H_
