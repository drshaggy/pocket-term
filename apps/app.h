#ifndef APP_H_
#define APP_H_

#include <iostream>
#include <queue>
#include "../drivers/display.h"

class App
{
protected:
    std::queue<char>  m_keyQueue;
    Display& m_display;
public:
    App(Display& display);
    virtual ~App() = default;
    int sendKey(char key);
    virtual int initialise();
    virtual int processNextKey();
};

#endif // APP_H_
