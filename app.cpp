#include "app.h"

App::App()
{};

int App::sendKey(char key){
    m_nextKey = key;
    return 0;
}
