#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>

class Display
{
public:
    Display();
    virtual ~Display() = default;
    virtual int initialise();
    virtual int redraw();
    virtual int clear();
    //text functions
    virtual int print(const std::string& text);
    virtual int println(const std::string& text);
};

#endif // DISPLAY_H_
