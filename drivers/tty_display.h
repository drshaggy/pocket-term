#ifndef TTY_DISPLAY_H_
#define TTY_DISPLAY_H_

#include <iostream>
#include <string>
#include "display.h"

class TtyDisplay : public Display
{
public:
    TtyDisplay();
    int initialise() override;
    int clear() override;
    int print(const std::string& text) override;
};

#endif // TTY_DISPLAY_H_
