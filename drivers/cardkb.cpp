#include "cardkb.h"
#include <iostream>

CardKB::CardKB(uint8_t address)
	: m_address(address)
{};

int CardKB::initialise()
{
    std::clog << "Initiallising CardKB Keyboard" << std::endl;
    if (!bcm2835_init()) {
        std::clog << "Failed to initialise CardKB Keyboard" << std::endl;
        return 1;
    }
    bcm2835_i2c_begin();                //Start I2C operations
    bcm2835_i2c_setSlaveAddress(m_address);  //I2C address
    bcm2835_i2c_set_baudrate(10000);    //1M baudrate
	return 0;
};

int CardKB::read()
{
	std::clog << "Attempting to read keyboard input";
	uint32_t len = 1;
 if (!bcm2835_i2c_read(m_buf, len)){
     std::clog << "Failed to read keyboard input" << std::endl;
     return 1;
 }
	return m_buf[0];
}
