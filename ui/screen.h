#ifndef SCREEN_H_
#define SCREEN_H_

#include <string>

class Screen
{
private:
    const uint8_t m_width;
    const uint8_t m_height;
    std::string m_statusBar;
public:
    Screen(const uint8_t width, const uint8_t height);
};

#endif // SCREEN_H_
