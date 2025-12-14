#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>

class Display
{
private:
    bool m_verticalOrientation;
public:
    Display(bool verticalOrientation);
    virtual ~Display() = default;
    virtual int redraw();
    virtual int clear();
    //text functions
    virtual int print(const std::string& text);
    virtual int printHighlighted(const std::string& text);
    virtual int println(const std::string& text);
};

#endif // DISPLAY_H_
