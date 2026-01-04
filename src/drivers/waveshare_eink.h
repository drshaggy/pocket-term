#ifndef WAVESHARE_EINK_H_
#define WAVESHARE_EINK_H_

#include "display.h"
#include <mutex>

struct Cursor
{
    int x;
    int y;
};

class WaveshareEink : public Display {
private:
    UBYTE* m_prevBuffer;
    UBYTE* m_frameBuffer;
    std::mutex m_bufferMutex;
    Cursor m_cursor;
    void clearWindow(const uint16_t& x, const uint16_t& y, const uint16_t& width, const  uint16_t& height);
public:
    WaveshareEink(bool verticalOrientation);
    virtual void drawText(const std::string& text, const uint16_t& x, const uint16_t& y, bool isHighlighted = false) override;
    virtual void drawBox(const uint16_t& width, const uint16_t& height, const bool hasBorder, const bool isFilled, const uint16_t& x, const uint16_t& y) override; 
    virtual void refresh() override;
    void refreshPartial();
    int clear() override;
};


#endif // WAVESHARE_EINK_H_
