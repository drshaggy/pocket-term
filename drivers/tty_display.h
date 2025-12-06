#ifndef TTY_DISPLAY_H_
#define TTY_DISPLAY_H_

#include <iostream>
#include "display.h"

class TtyDisplay : public Display
{
public:
    TtyDisplay();
    int initialise() override;
};

#endif // TTY_DISPLAY_H_
