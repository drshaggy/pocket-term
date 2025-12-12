cmake_minimum_required(VERSION 3.15)
project(pocket-term VERSION 1.0.0 LANGUAGES CXX)

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

# Source files
set(SOURCES
    main.cpp
    os.cpp
    app_manager.cpp
    event.cpp
    ui/ui.cpp
    ui/screen.cpp
    utilities.cpp
    drivers/event_source.cpp
    drivers/cardkb.cpp
    drivers/sim800l.cpp
    drivers/display.cpp
    drivers/tty_display.cpp
    apps/app.cpp
    apps/home.cpp
    apps/launcher.cpp
)

# Headers
set(HEADERS
    ui/ui.h
    ui/screen.h
    os.h
    app_manager.h
    event.h
    utilities.h
    drivers/event_source.h
    drivers/cardkb.h
    drivers/sim800l.h
    drivers/display.h
    drivers/tty_display.h
    apps/app.h
    apps/home.h
    apps/launcher.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${BCM2835_LIBRARY})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
