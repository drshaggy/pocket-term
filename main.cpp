#include <iostream>
#include "os.h"
#include "apps/home.h"
#include "event.h"
#include "ui.h"
#include <thread>
#include <memory>

using namespace std::chrono_literals;

// auto main(int argc, char *argv[]) -> int {
int main() {
    std::clog << "Starting Pocket Terminal OS" << std::endl;
    OS os;

    os.run();

    os.cleanUp();
    return 0;
}
