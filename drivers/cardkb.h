#ifndef CARDKB_H_
#define CARDKB_H_

#include <bcm2835.h>

class CardKB
{
private:
    char m_buf[1];
    [[maybe_unused]]int& m_address;
public:
    CardKB(int& address);
    int initialise();
    int read();

};

#endif // CARDKB_H_
