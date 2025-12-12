#include "sim800l.h"

#include <spdlog/spdlog.h>
#include <stdio.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <spdlog/spdlog.h>

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
    char buffer[512] = {0};
    int bytes = read(m_serialPort, buffer, sizeof(buffer) - 1);

    if (bytes > 0) {
        buffer[bytes] = '\0';
        std::string response(buffer);

        // Check for new SMS notification
        if (response.find("+CMTI:") != std::string::npos) {
            spdlog::info("New SMS received: {}", response);
            char buffer[512] = {0};
            int bytes = read(m_serialPort, buffer, sizeof(buffer) - 1);

            if (bytes > 0) {
                buffer[bytes] = '\0';
                std::string response(buffer);

                // Check for new SMS notification
                if (response.find("+CMTI:") != std::string::npos) {
                    spdlog::info("New SMS received: {}", response);
                    // Extract message index (e.g., from "+CMTI: "SM",5")
                    size_t pos = response.find_last_of(',');
                    if (pos != std::string::npos) {
                        int index = std::stoi(response.substr(pos + 1));
                        std::string response;
                        if (readSMS(index, response)) {
                            spdlog::debug("SMS index: {}, content: {}", index, response);
                            // Create Event here
                        }
                    }
                }
            }
        }
    }
}

void Sim800l::end() {
    close(m_serialPort);
}

bool Sim800l::checkConnection() {
    unsigned char msg[] = { 'A', 'T', '\r' };
    write(m_serialPort, msg, sizeof(msg));
    char readBuf [256] {0};
    usleep(500000);
    int n = read(m_serialPort, &readBuf, sizeof(readBuf));
    if (n > 0) {
        spdlog::debug("SIM800L Response: {}", readBuf);
        return true;
    } else {
        spdlog::error("No Response from SIM800L");
        return false;
    }
}

int Sim800l::readSMS(int index, std::string& response) {
    std::string cmd = "AT+CMGR=" + std::to_string(index) + "\r";
    spdlog::debug("Command: {}", cmd);
    write(m_serialPort, cmd.c_str(), cmd.length());

    usleep(500000);

    char readBuf [256] {0};
    int n = read(m_serialPort, &readBuf, sizeof(readBuf));
    if (n > 0) {
        spdlog::debug("SIM800L Response: {}", readBuf);
        response = std::string(readBuf);
        return 0;
    }
    return 1;
}
