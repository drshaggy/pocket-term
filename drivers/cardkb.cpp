#include "cardkb.h"
#include <spdlog/spdlog.h>

CardKB::CardKB(uint8_t address) : m_address(address)
{
    if (!bcm2835_init()) {
        spdlog::error("BCM2835 driver failed to initialise");
    } else {
        spdlog::info("BCM Driver Initialised");
    }

    spdlog::info("Starting I2C Operations");
    if (!bcm2835_i2c_begin()) {
        spdlog::error("I2C Operatiions failed to start, are you running as root?");
    } else {
        spdlog::info("I2C Operations Started");
        bcm2835_i2c_setSlaveAddress(m_address);  //I2C address
        bcm2835_i2c_set_baudrate(100000);    //100k baudrate
    }
};

int CardKB::read() {
    m_buf[0] = 0;
    uint32_t len = 1;
    bcm2835_i2c_read(m_buf, len);
    return m_buf[0];
}

// override EventSource.poll
void CardKB::poll() {
    char buf[256];
    buf[0] = 0;
    uint32_t len = 1;
    bcm2835_i2c_read(buf, len);
    if (buf[0]) {
        Event e = Event::createKeyEvent(buf[0], 0);
        m_eventQueue.push(std::move(e));
    }
}

void CardKB::end() {
    bcm2835_i2c_end();
}
