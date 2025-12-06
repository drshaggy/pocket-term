#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display
{
public:
    Display();
    virtual ~Display() = default;
    virtual int initialise();
    virtual int redraw();
};

#endif // DISPLAY_H_
