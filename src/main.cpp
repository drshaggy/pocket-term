#include "core/os.h"
#include "core/logging.h"

#include <spdlog/spdlog.h>

auto main(int argc, char *argv[]) -> int {
    setupLogging();
    spdlog::info("Starting Pocket Terminal OS");
    // bool simulateHardware = false;
    for (int i = 1; i < argc; ++i) {  // Start at 1 (skip program name)
        if (std::string(argv[i]) == "--simulate") {
            // simulateHardware = true;
            break;
        }
    }
    std::unique_ptr<OS> os = launchRootActor<OS>();

    return 0;
}

