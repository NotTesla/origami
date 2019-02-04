# Dependencies
## glfw
- Download glfw-3.2.1 from [here](https://www.glfw.org/download.html)
- Extract folder and copy your desired lib into `origami/deps/libs`
- TODO: right now the lib must be called libglfw or it probably won't find it
-       I would like to fix any hardcoding in the CMakeLists so there aren't any
-       issues building regardless of compiler or platform used

# Getting Started

## Windows
Get MinGW from here: 

1. mkdir build
2. cd build
3. cmake .. -G "MinGW Makefiles"
4. mingw32-make ; src/origami.exe
if you want to see logging output, call
5. src/origami_debug.exe

## Mac
TODO: I don't have a mac, so it's a bit hard to document the process
I would imagine it will be similar to the Linux guide once I'm done that...

## Linux
TODO: