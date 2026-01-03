#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../../external/waveshare/Config/DEV_Config.h"

#include <string>

class Screen;
class StatusBar;

class Display
{
protected:
    bool m_verticalOrientation;
    UDOUBLE m_displaySize;
    uint16_t m_width;
    uint16_t m_height;
    uint16_t m_rotation;
    bool m_ready = false;
public:
    Display(bool verticalOrientation);
    virtual ~Display() = default;
    bool isReady() const {return m_ready;}
    int draw(Screen& screen);
    int draw(StatusBar& statusBar);
    virtual void refresh() = 0;
    virtual int clear();
    //text functions
    virtual int print(const std::string& text);
    virtual int printHighlighted(const std::string& text);
    virtual int println(const std::string& text);
    //widget functions
    virtual void drawText(const std::string& text, const uint8_t& x, const uint8_t& y, bool isHighlighted = false) = 0;
};

#endif // DISPLAY_H_
