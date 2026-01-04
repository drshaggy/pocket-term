#ifndef HOME_H_
#define HOME_H_

#include "app.h"

class Home : public App
{
private:
    std::string input = "";
    uint8_t m_selectedApp{0};
    std::vector<std::string> m_appList{"Messages", "Phone", "Calculator"};
public:
    Home(Actor& caller);
    int initialise() override;
    virtual void handleMessage(Message& message) override;
};

#endif // HOME_H_
