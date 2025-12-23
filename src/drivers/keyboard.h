#ifndef KEYBOARD_H_
#define KEYBOARD_H_

class Keyboard
{
public:
	Keyboard();
	virtual ~Keyboard();
	virtual void cleanUp();
	virtual char read();
};

#endif // KEYBOARD_H_
