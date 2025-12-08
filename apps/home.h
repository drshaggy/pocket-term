#ifndef HOME_H_
#define HOME_H_

#include "app.h"
#include "../utilities.h"

class Home : public App
{
public:
	using App::App;
	int initialise() override;
	int processSpecificEvent(const Event& e) override;
};

#endif // HOME_H_
