#ifndef CARDKB_H_
#define CARDKB_H_

#include <bcm2835.h>

class CardKB
{
private:
    int& m_address;
public:
	CardKB(int& address);
};

#endif // CARDKB_H_
