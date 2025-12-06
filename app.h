#ifndef APP_H_
#define APP_H_

class App
{
private:
    char m_nextKey;
public:
    App();
    virtual ~App() = default;
    int sendKey(char key);
    virtual int initialise();
};

#endif // APP_H_
