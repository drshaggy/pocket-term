#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "app.h"

class Terminal : public App
{
public:
	using App::App;
	virtual int initialise() override;
};

#endif // TERMINAL_H_
