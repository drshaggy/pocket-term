#ifndef TTY_DISPLAY_H_
#define TTY_DISPLAY_H_

#include <iostream>
#include <thread>
#include <string>
#include "display.h"

using namespace std::chrono_literals;

class TtyDisplay : public Display
{
public:
    TtyDisplay();
    int initialise() override;
    int clear() override;
    int print(const std::string& text) override;
};

#endif // TTY_DISPLAY_H_
