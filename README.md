# Robot Visualiser in C

This project has been created for the robot project in
COMPSYS301. It is meant to be able to visualise path finding
code.

## Requirements

- `pkg-config`: Finds the correct verisons of installed
  libraries ([link](https://www.freedesktop.org/wiki/Software/pkg-config/))
- `raylib`: C library for drawing visuals
  ([link](https://www.raylib.com/))
- A C compiler

## Building

If you're on macOS or Linux, you can simply just install the
dependencies listed above, and then run `./build.sh`.

If you're on Windows, you have to do incite the CMake chant:
```pwsh
mkdir build # Create a build directory
cd build && cmake .. # Build from that directory so the build files are in one place
cmake --build . # Build the project
```
