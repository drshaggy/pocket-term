#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>
#include "../../external/waveshare/Config/DEV_Config.h"

class Display
{
protected:
    bool m_verticalOrientation;
    UDOUBLE m_displaySize;
    uint16_t m_width;
    uint16_t m_height;
    uint16_t m_rotation;
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
