#include <iostream>
#include "drivers/cardkb.h"
#include "drivers/tty_display.h"
#include "apps/launcher.h"
#include <chrono>
#include <thread>
#include <memory>

using namespace std::chrono_literals;

// auto main(int argc, char *argv[]) -> int {
int main() {
    std::clog << "Starting Pocket Terminal OS" << std::endl;
    //Initialise drivers
    uint8_t addr = 0x5f;
    CardKB keyboard(addr);
    if (keyboard.initialise()){
        std::cerr << "Failed to initialise keyboard" << std::endl;
        return 1;
    }
    std::unique_ptr<Display> display = std::make_unique<TtyDisplay>();
    if (display->initialise()){
        std::cerr << "Failed to initialise display" << std::endl;
        return 1;
    }
    //Load default app
    std::unique_ptr<App> app = std::make_unique<Launcher>(*display);
    if(app->initialise()){
       std::cerr << "Default app failed to load" << std::endl;
       return 1;
    }
    //Main loop
    while(true)
    {
        char key = static_cast<char>(keyboard.read());
        if(key) {
            app->sendKey(key);
            app->processNextKey();
        }
        std::this_thread::sleep_for(10ms);
    }
    //Clean up
    keyboard.end();
    return 0;
}
