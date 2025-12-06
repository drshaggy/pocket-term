#include "cardkb.h"

CardKB::CardKB(int& address)
	: m_address(address)
{};

int CardKB::initialise()
{
	if (!bcm2835_init())
		return 1;
	bcm2835_i2c_begin();                //Start I2C operations
    bcm2835_i2c_setSlaveAddress(0x20);  //I2C address
    bcm2835_i2c_set_baudrate(10000);    //1M baudrate
	return 0;
};

int CardKB::read()
{
	uint32_t len = 0;
	return bcm2835_i2c_read(m_buf, len);
}
