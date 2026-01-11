#!/bin/bash
set -e  # Exit on any error
set -u  # Exit on undefined variable

echo "========================================="
echo "Pocket Terminal OS - Raspberry Pi Setup"
echo "========================================="
echo ""

# Verify we're on ARM architecture (Raspberry Pi)
ARCH=$(uname -m)
if [[ "$ARCH" != "armv7l" && "$ARCH" != "aarch64" ]]; then
    echo "Warning: This doesn't appear to be a Raspberry Pi (detected: $ARCH)"
    read -p "Continue anyway? (y/N) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

# Step 1: Update system packages
echo "Step 1/6: Updating system packages..."
sudo apt update
sudo apt upgrade -y
echo "✓ System updated"
echo ""

# Step 2: Install build essentials
echo "Step 2/6: Installing build essentials..."
sudo apt install -y \
    build-essential \
    cmake \
    git \
    autoconf \
    automake \
    libtool
echo "✓ Build tools installed"
echo ""

# Step 3: Install spdlog library
echo "Step 3/6: Installing spdlog library..."
sudo apt install -y libspdlog-dev
echo "✓ spdlog installed"
echo ""

# Step 4: Install BCM2835 library for GPIO/SPI/I2C access
echo "Step 4/6: Installing BCM2835 library..."

# Check if already installed
if ldconfig -p | grep -q "libbcm2835.so"; then
    echo "BCM2835 already installed, skipping..."
else
    cd /tmp
    # Use GitHub mirror (more reliable than airspayce.com)
    git clone https://github.com/smart-facility/bcm2835.git
    cd bcm2835
    autoreconf -fi
    ./configure
    make
    sudo make install
    cd ~
    rm -rf /tmp/bcm2835
    echo "✓ BCM2835 library installed"
fi
echo ""

# Step 5: Set up user permissions for GPIO and serial access
echo "Step 5/6: Setting up user permissions..."
sudo usermod -a -G gpio,dialout $USER
echo "✓ Added $USER to gpio and dialout groups"
echo "  (You'll need to log out and back in for this to take effect)"
echo ""

# Step 6: Build the project
echo "Step 6/6: Building Pocket Terminal OS..."
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_ROOT"
./scripts/build.sh
echo "✓ Build complete"
echo ""

# Final instructions
echo "========================================="
echo "Setup Complete!"
echo "========================================="
echo ""
echo "Next steps:"
echo "  1. Log out and back in (for group permissions)"
echo "  2. Run: sudo ./scripts/run.sh"
echo ""
echo "Note: The application requires sudo to access GPIO hardware."
echo ""
