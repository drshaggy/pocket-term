#ifndef ENUMS_H_
#define ENUMS_H_

enum SpecialKey {
	DOWN,
	UP,
	LEFT,
	RIGHT,
	ESCAPE,
	TAB,
	BACKSPACE,
	ENTER
}; 

enum MessageType {
	KEY_PRESS,
 DOWN_KEY_PRESS,
	TICK,
 ACKNOWLEDGE,
 SCREEN,
 SUBSCRIBE
};

#endif // ENUMS_H_
