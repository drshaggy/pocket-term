#ifndef WAVESHARE_EINK_H_
#define WAVESHARE_EINK_H_

#include "display.h"
#include "../../external/waveshare/Config/DEV_Config.h"

class WaveshareEink : public Display {
private:
    UBYTE* m_frameBuffer;
    UDOUBLE m_displaySize;
public:
    WaveshareEink(bool verticalOrientation);
};


#endif // WAVESHARE_EINK_H_
