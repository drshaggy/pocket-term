#include "cardkb.h"
#include <iostream>

CardKB::CardKB(uint8_t address)
	: m_address(address)
{};

int CardKB::initialise()
{
    std::clog << "Initiallising CardKB Keyboard" << std::endl;
    if (!bcm2835_init()) {
        std::cerr << "Failed to initialise CardKB Keyboard" << std::endl;
        return 1;
    }
    std::clog << "bcm2835 Initialised" << std::endl << "Starting I2C Operations" << std::endl;
    if (!bcm2835_i2c_begin()) {
			std::cerr << "I2C failed to begin, are you running as root?" << std::endl;
			return 1;
    }                //Start I2C operations
    std::clog << "I2C Operations started" << std::endl
			  << "Setting slave address and baud rate" << std::endl;
    bcm2835_i2c_setSlaveAddress(m_address);  //I2C address
    bcm2835_i2c_set_baudrate(10000);    //1M baudrate
    std::clog << "Address and baud rate set" << std::endl;
    return 0;
};

int CardKB::read()
{
    std::clog << "Attempting to read keyboard input" << std::endl;
    uint32_t len = 1;
    uint8_t data = bcm2835_i2c_read(m_buf, len);
    // return m_buf[0];
    return data;
}
