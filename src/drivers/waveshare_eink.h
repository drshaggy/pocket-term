#ifndef WAVESHARE_EINK_H_
#define WAVESHARE_EINK_H_

#include "display.h"

struct Cursor
{
    int x;
    int y;
};

class WaveshareEink : public Display {
private:
    Cursor m_cursor;
public:
    WaveshareEink(bool verticalOrientation);
    int println(const std::string& text) override;
    int print(const std::string& text) override;
    int printHighlighted(const std::string& text) override;
};


#endif // WAVESHARE_EINK_H_
