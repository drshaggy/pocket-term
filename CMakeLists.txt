cmake_minimum_required(VERSION 3.15)
project(pocket-term VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Find bcm2835 library
find_library(BCM2835_LIBRARY bcm2835 REQUIRED)

# Source files
set(SOURCES
    main.cpp
    event.cpp
    ui.cpp
    drivers/event_source.cpp
    drivers/cardkb.cpp
    drivers/display.cpp
    drivers/tty_display.cpp
    apps/app.cpp
    apps/home.cpp
    apps/launcher.cpp
)

# Headers
set(HEADERS
    event.h
    ui.h
    drivers/event_source.h
    drivers/cardkb.h
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
