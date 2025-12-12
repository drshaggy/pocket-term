#ifndef SIM800L_H_
#define SIM800L_H_

#include "event_source.h"

#include <string>

class Sim800l : EventSource{
private:
	const std::string m_device;
	const int m_baudRate;
	int m_serialPort;
public:
	Sim800l(std::string device, int baudRate);
	void poll() override;
};

#endif // SIM800L_H_
