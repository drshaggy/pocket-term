#include "sim800l.h"

#include <stdio.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <iostream>

Sim800l::Sim800l(std::string device, int baudRate)
    : m_device(device), m_baudRate(baudRate)
{
    m_serialPort = open(device.c_str(), O_RDWR);
    if (m_serialPort < 0) {
        std::clog << "Error connecting to device" << std::endl;
    } else {
        std::clog << "SIM880L Connected" << std::endl;
    }
}

void Sim800l::poll() {

}

void Sim800l::end() {
    close(m_serialPort);
}
