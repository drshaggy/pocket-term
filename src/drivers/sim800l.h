#ifndef SIM800L_H_
#define SIM800L_H_

#include "event_source.h"

#include <string>

class Sim800l : EventSource{
private:
    const std::string m_device;
    const int m_baudRate;
    int m_serialPort;
    std::string m_readBuffer;
public:
    Sim800l(std::string device, int baudRate);
    void end();
    void poll() override;
    bool checkConnection();
    int readSMS(int index, std::string& response);
};

#endif // SIM800L_H_
