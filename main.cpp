#include <iostream>
#include "drivers/cardkb.h"
#include <chrono>
#include <thread>

// auto main(int argc, char *argv[]) -> int {
int main() {
    std::clog << "Starting Pocket Terminal OS" << std::endl;
    uint8_t addr = 0x5f;
    CardKB keyboard(addr);
    if (keyboard.initialise()){
        std::cerr << "Failed to initialise keyboard" << std::endl;
        return 1;
    }
    while(true)
    {
        char key = static_cast<char>(keyboard.read());
        std::cout << key;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
