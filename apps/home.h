#ifndef HOME_H_
#define HOME_H_

#include "app.h"

class Home : public App
{
public:
	using App::App;
	int initialise() override;
	int processNextEvent(Event e) override;
};

#endif // HOME_H_
