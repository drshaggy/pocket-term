#!/bin/bash
set -e  # Exit on error

# Determine project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

echo "Building pocket-term..."
echo "Project root: $PROJECT_ROOT"

# Change to project root
cd "$PROJECT_ROOT"

# Create and enter build directory
mkdir -p build
cd build

# Configure and build
echo "Running CMake..."
cmake ..

echo "Building..."
cmake --build . -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo "✓ Build complete!"
echo "Binary: $PROJECT_ROOT/build/pocket-term"
