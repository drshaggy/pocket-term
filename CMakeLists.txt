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
    drivers/cardkb.cpp
    app.cpp
)

# Headers
set(HEADERS
    drivers/cardkb.h
    app.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${BCM2835_LIBRARY})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
