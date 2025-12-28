#ifndef HOME_H_
#define HOME_H_

#include "app.h"

class Home : public App
{
private:
    std::string input;
public:
    Home(Actor& caller);
    int initialise() override;
    int processSpecificMessage(Message& m) override;
};

#endif // HOME_H_
