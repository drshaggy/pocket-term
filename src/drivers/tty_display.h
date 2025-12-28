#ifndef TTY_DISPLAY_H_
#define TTY_DISPLAY_H_

#include <string>
#include "display.h"

class TtyDisplay : public Display
{
public:
    TtyDisplay(bool verticalOrientation);
    int clear() override;
    int print(const std::string& text) override;
    int printHighlighted(const std::string& text) override;
    int println(const std::string& text) override;
    virtual void drawText(const std::string& text, const uint8_t& x, const uint8_t& y) override;
    virtual void refresh() override {};
};

#endif // TTY_DISPLAY_H_
