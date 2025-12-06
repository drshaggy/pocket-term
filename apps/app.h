#ifndef APP_H_
#define APP_H_

#include "../drivers/display.h"

class App
{
private:
    char m_nextKey;
    Display& m_display;
public:
    App(Display& display);
    virtual ~App() = default;
    int sendKey(char key);
    virtual int initialise();
};

#endif // APP_H_
