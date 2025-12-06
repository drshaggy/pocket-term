#include "app.h"

App::App()
{};

int App::initialise(){
    return 1;
}

int App::sendKey(char key){
    m_nextKey = key;
    return 0;
}
