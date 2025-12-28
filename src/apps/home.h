#ifndef HOME_H_
#define HOME_H_

#include "app.h"

class Home : public App
{
public:
    Home(Actor& caller);
    int initialise() override;
    int processSpecificMessage(Message& e) override;
};

#endif // HOME_H_
