#ifndef INPUT_H_
#define INPUT_H_

#include "../core/actor.h"

class Input : public Actor
{
protected:
	virtual void actorCore() override;
public:
	Input();
	virtual ~Input() = default;
};

#endif // INPUT_H_
