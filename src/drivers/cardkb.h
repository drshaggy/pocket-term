#ifndef CARDKB_H_
#define CARDKB_H_

#include <bcm2835.h>
#include "message_source.h"

class CardKB : public MessageSource
{
private:
    char m_buf[256];
    uint8_t  m_address;
public:
    CardKB(uint8_t address);
    void end();
    int read();
    void poll() override;

};

#endif // CARDKB_H_
