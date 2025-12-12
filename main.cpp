#include "os.h"
#include "logging.h"

// auto main(int argc, char *argv[]) -> int {
int main() {
    setupLogging();
    spdlog::info("Starting Pocket Terminal OS");
    OS os;

    os.run();

    os.cleanUp();
    return 0;
}

