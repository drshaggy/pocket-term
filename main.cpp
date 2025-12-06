#include <iostream>
#include "drivers/cardkb.h"
#include <chrono>
#include <thread>

// auto main(int argc, char *argv[]) -> int {
int main() {
    int addr = 0x5f;
    CardKB keyboard(addr);
    keyboard.initialise();
    while(true)
    {
        std::cout << keyboard.read();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
