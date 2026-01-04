#ifndef TTY_DISPLAY_H_
#define TTY_DISPLAY_H_

#include <string>
#include "display.h"

class TtyDisplay : public Display
{
public:
    TtyDisplay(bool verticalOrientation);
    int clear() override;
    virtual void drawText(const std::string& text, const uint16_t& x, const uint16_t& y, bool isHighlighted) override;
    virtual void drawBox(const uint16_t& width, const uint16_t& height, const bool hasBorder, const bool isFilled, const uint16_t& x, const uint16_t& y) override; 
    virtual void refresh() override {};
};

#endif // TTY_DISPLAY_H_
