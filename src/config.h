#ifndef CONFIG_H_
#define CONFIG_H_

#ifdef RPI
constexpr bool SIMULATE_HARDWARE = false;
#else
constexpr bool SIMULATE_HARDWARE = true;
#endif

#endif // CONFIG_H_
