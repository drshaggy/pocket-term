#include "sim800l.h"

#include <spdlog/spdlog.h>
#include <stdio.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <termios.h> // Contains POSIX terminal control definitions
#include <errno.h> // Error integer and strerror() function
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
        // Set u serial port for UART
        termios tty;
        if (tcgetattr(m_serialPort, &tty)!= 0) {
            spdlog::error("Error {} from tcgetattr: {}", errno, strerror(errno));
        } else {
            tty.c_cflag &= ~PARENB; //Disable Parity
            tty.c_cflag |= CSTOPB; //One Stop Bit
            tty.c_cflag &= ~CSIZE; //Clear size
            tty.c_cflag |= CS8; //Set 8 bits size
            tty.c_cflag &= ~CRTSCTS; //Disable hardware flow control
            tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

            tty.c_lflag &= ~ICANON; //Disable canonical mode
            tty.c_lflag &= ~ECHO; // Disable echo
            tty.c_lflag &= ~ECHOE; // Disable erasure
            tty.c_lflag &= ~ECHONL; // Disable new-line echo
            tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP

            tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
            tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

            tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
            tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

            tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
            tty.c_cc[VMIN] = 0;

            // Set in/out baud rate to be 9600
            cfsetispeed(&tty, B9600);
            cfsetospeed(&tty, B9600);

            // Save tty settings, also checking for error
            if (tcsetattr(m_serialPort, TCSANOW, &tty) != 0) {
                spdlog::error("Error {} from tcsetattr: {}", errno, strerror(errno));
            }
        }
        if (checkConnection()) {
            spdlog::info("Connection to SIM800L established");
        } else {
            spdlog::error("No Connection to SIM800L");
        }
    }
}

void Sim800l::poll() {
    std::string response;
    readSerialLine(response);

    if (response.find("+CMTI:") != std::string::npos) {
        spdlog::info("New SMS received. UCR: {}", response);
        // Extract message index (e.g., from "+CMTI: "SM",5")
        size_t pos = response.find_last_of(',');
        if (pos != std::string::npos) {
            int index = std::stoi(response.substr(pos + 1));
            std::string msg;
            if (!readSMS(index, msg)) {
                spdlog::debug("SMS index: {}, content: {}", index, msg);
                // Create Event here
            } else {
                spdlog::error("Failed to read SMS Message");
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

    std::string sr;
    int success {1};
    success = readSerialLine(sr);
    response = sr;
    return success;
}

int Sim800l::readSerialLine(std::string& response) {
    char buf[512] = {0};
    size_t start {std::string::npos};
    size_t end {std::string::npos};
    response.clear();
    while (end == std::string::npos) {
        int bytes = read(m_serialPort, buf, sizeof(buf) - 1);
        if (bytes <= 0) {
            return 1;
        }
        buf[bytes] = '\0';
        response += buf;
        spdlog::debug("Read Buffer: {}", response);
        start = response.find("\n");
        if (start != std::string::npos) {
            end =  response.find("\n", start + 1);
        }
    }
    return 0;
}
