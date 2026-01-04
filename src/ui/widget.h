#ifndef WIDGET_H_
#define WIDGET_H_

#include <memory>

class Display;

class Widget
{
protected:
    uint16_t m_boundWidth;
    uint16_t m_boundHeight;
public:
    virtual ~Widget() = default;
    virtual void render(Display* display, const uint16_t& x, const uint16_t& y ) const = 0;
    virtual std::unique_ptr<Widget> clone() = 0;
};

#endif // WIDGET_H_
