#include "input.h"

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

Input::Input() : Actor()
{
    
}

void Input::actorCore() {
    spdlog::debug("Actor {} Running", getActorId());
    std::this_thread::sleep_for(200ms);
}
