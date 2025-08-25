
# ScreenCapture

Simple screen capture utility for Linux using **X11** and **OpenCV**.  
Supports FPS counter overlay and configurable resolution from command-line arguments.

## Features
- Capture screen area using X11 (`XGetImage`)
- Display result in OpenCV window
- Show live FPS in top-right corner
- Configurable resolution at launch

## Requirements
- Linux with X11
- CMake >= 3.5
- OpenCV (tested on 4.2)
- X11 development libraries

Install dependencies on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install cmake g++ libopencv-dev libx11-dev
````

## Build

```bash
git clone https://github.com/Amin-mansurov/ScreenCapture.git
cd ScreenCapture
mkdir build && cd build
cmake ..
make
```

## Run

Usage:

```bash
./ScreenCapture <width> <height>
```

Example (capture 1280x720):

```bash
./ScreenCapture 1280 720
```

Press **q** in the window to quit.
