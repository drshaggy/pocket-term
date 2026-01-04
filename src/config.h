#ifndef CONFIG_H_
#define CONFIG_H_

#include <cstdint>

#ifdef RPI
constexpr bool SIMULATE_HARDWARE = false;
#else
constexpr bool SIMULATE_HARDWARE = true;
#endif

constexpr uint16_t SCREEN_HEIGHT = 480;
constexpr uint16_t SCREEN_WIDTH = 800;

constexpr uint16_t SEGMENT_HEIGHT = 24;
constexpr uint16_t SEGMENT_WIDTH = 17;

#endif // CONFIG_H_
