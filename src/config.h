#ifndef CONFIG_H_
#define CONFIG_H_

#include <cstdint>

#ifdef RPI
constexpr bool SIMULATE_HARDWARE = false;
#else
constexpr bool SIMULATE_HARDWARE = true;
constexpr uint8_t SEGMENT_HEIGHT = 20;
constexpr uint8_t SEGMENT_WIDTH = 20;
#endif

#endif // CONFIG_H_
