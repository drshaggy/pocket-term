#ifndef CARDKB_H_
#define CARDKB_H_

#include <bcm2835.h>
#include "keyboard.h"

class CardKB : public Keyboard
{
private:
    char m_buf[256];
    uint8_t  m_address;
public:
    CardKB(uint8_t address);
    virtual ~CardKB();
    virtual void cleanUp() override;
    virtual char read() override;
    void poll();

};

#endif // CARDKB_H_
