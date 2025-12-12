#include "sim800l.h"

#include <spdlog/spdlog.h>
#include <stdio.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

Sim800l::Sim800l(std::string device, int baudRate)
    : m_device(device), m_baudRate(baudRate)
{
    m_serialPort = open(device.c_str(), O_RDWR);
    if (m_serialPort < 0) {
        spdlog::error("Error connecting to SIM800L Module");
    } else {
        spdlog::info("SIM800L Module Initialised");
        if (checkConnection()) {
            spdlog::info("Connection to SIM800L established");
        } else {
            spdlog::error("No Connection to SIM800L");
        }
    }
}

void Sim800l::poll() {

}

void Sim800l::end() {
    close(m_serialPort);
}

bool Sim800l::checkConnection() {
    unsigned char msg[] = { 'A', 'T', '\r' };
    write(m_serialPort, msg, sizeof(msg));
    char readBuf [256];

    int n = read(m_serialPort, &readBuf, sizeof(readBuf));
    return n > 0;
}
