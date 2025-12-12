# Pocket Terminal OS
An operating system written in C++ for the pocket terminal "dumb phone" cyber deck. 

## BCM2835 Library
This operating system relies on the BCM2835 library from www.airspayce.com for I2C and SPI communication. Here are the steps for installing

```
cd ~
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.58.tar.gz
tar xvfz bcm2835-1.77.tar.gz
cd bcm2835-1.77/
./configure
make
sudo make install
```

## Building

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

```
cd build
./pocket-term
```

# Usage

Press ESC to clear the scree:n
`

