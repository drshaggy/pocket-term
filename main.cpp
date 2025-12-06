#include <iostream>
#include "drivers/cardkb.h"
#include <chrono>
#include <thread>

// auto main(int argc, char *argv[]) -> int {
int main() {
    std::clog << "Starting Pocket Terminal OS" << std::endl;
    int addr = 0x5f;
    CardKB keyboard(addr);
    if (!keyboard.initialise())
        return 1;
    while(true)
    {
        std::clog << keyboard.read() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
