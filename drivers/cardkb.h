#ifndef CARDKB_H_
#define CARDKB_H_

#include <bcm2835.h>

class CardKB
{
private:
    char m_buf[256];
    [[maybe_unused]]uint8_t  m_address;
public:
    CardKB(uint8_t address);
    int initialise();
    void end();
    int read();

};

#endif // CARDKB_H_
