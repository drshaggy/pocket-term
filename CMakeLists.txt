cmake_minimum_required(VERSION 3.15)
project(pocket-term VERSION 1.0.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for LSP/Flycheck
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Find bcm2835 library
find_library(BCM2835_LIBRARY bcm2835 REQUIRED)
find_package(spdlog REQUIRED)

# Source files
set(SOURCES
    external/waveshare/Config/DEV_Config.c
    external/waveshare/Fonts/font12.c
    external/waveshare/Fonts/font24.c
    external/waveshare/GUI/GUI_Paint.c
    external/waveshare/GUI/GUI_BMPfile.c
    external/waveshare/EPD_4in26.c
    src/main.cpp
    src/core/actor.cpp
    src/core/os.cpp
    src/core/logging.cpp
    src/core/app_manager.cpp
    src/core/enqueuer.cpp
    src/core/message.cpp
    src/core/time_utils.cpp
    src/drivers/message_source.cpp
    src/drivers/keyboard.cpp
    src/drivers/cardkb.cpp
    src/drivers/sim800l.cpp
    src/drivers/display.cpp
    src/drivers/tty_display.cpp
    src/drivers/waveshare_eink.cpp
    src/input/input.cpp
    src/ui/ui.cpp
    src/ui/widget.cpp
    src/ui/vertical_widget.cpp
    src/ui/text_widget.cpp
    src/ui/input_widget.cpp
    src/ui/screen.cpp
    src/ui/status_bar.cpp
    src/apps/app.cpp
    src/apps/home.cpp
    src/apps/launcher.cpp
    src/apps/terminal.cpp
)

# Headers
set(HEADERS
    external/waveshare/Config/DEV_Config.h
    external/waveshare/Fonts/fonts.h
    external/waveshare/GUI/GUI_Paint.h
    external/waveshare/GUI/GUI_BMPfile.h
    external/waveshare/EPD_4in26.h
    src/core/actor.h
    src/core/os.h
    src/core/logging.h
    src/core/app_manager.h
    src/core/enqueuer.h
    src/core/message.h
    src/core/time_utils.h
    src/drivers/message_source.h
    src/drivers/keyboard.h
    src/drivers/cardkb.h
    src/drivers/sim800l.h
    src/drivers/display.h
    src/drivers/tty_display.h
    src/drivers/waveshare_eink.h
    src/input/input.h
    src/ui/ui.h
    src/ui/widget.h
    src/ui/text_widget.h
    src/ui/input_widget.h
    src/ui/vertical_widget.h
    src/ui/screen.h
    src/ui/status_bar.h
    src/apps/app.h
    src/apps/home.h
    src/apps/launcher.h
    src/apps/terminal.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Detect actual Raspberry Pi (ARM processor + Linux OS)
if((CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Building for Raspberry Pi with BCM2835 support")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RPI USE_BCM2835_LIB)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${BCM2835_LIBRARY})
else()
    message(STATUS "Building in simulation mode")
endif()

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${BCM2835_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
