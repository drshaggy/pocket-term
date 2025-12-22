#ifndef SIM800L_H_
#define SIM800L_H_

#include "message_source.h"

#include <string>

class Sim800l : MessageSource{
private:
    const std::string m_device;
    const int m_baudRate;
    int m_serialPort;
public:
    Sim800l(std::string device, int baudRate);
    void end();
    void poll() override;
    bool checkConnection();
    int readSMS(int index, std::string& response);
    int readSerialLine(std::string& response);
    int readSerialMuiltiLine(std::string& response);
};

#endif // SIM800L_H_
