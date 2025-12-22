#include "input.h"

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

Input::Input() : Actor()
{
    
}

void Input::actorCore() {
    spdlog::debug("Input Loop Running");
    std::this_thread::sleep_for(20ms);
}
