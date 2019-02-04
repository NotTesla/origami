# CMakeList.txt : CMake project for origami, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(DEPS "../deps")
set(GLFW_PATH "${DEPS}/glfw-3.2.1")
set(RES_PATH "../res")

FILE(GLOB ORIGAMI *.c common/*.c)
# set(ORIGAMI "app.c" "device_interface.c" "file_utils.c" "main.c" "tuple_interface.c" "utils.c")
# set(SHADERS "${RES_PATH}/shaders/default.vsh" "${RES_PATH}/shaders/default.fsh")

find_library(GLFW_LIB libglfw3 HINTS "${DEPS}/libs")
link_directories("${DEPS}/libs")

# Add source to this project's executable.
add_executable (origami WIN32 ${ORIGAMI} "${GLFW_PATH}/include/GLFW/glfw3.h" "${DEPS}/glad.c")

# Build without console
add_executable (origami_debug ${ORIGAMI} "${GLFW_PATH}/include/GLFW/glfw3.h" "${DEPS}/glad.c")

set(BINARIES origami origami_debug)
set(INCLUDES "${GLFW_PATH}/include/" "common/" "${DEPS}")
set(LIBRARIES "${GLFW_LIB}")

# TODO: this is redundant... didn't seem to work when I used ${BINARIES} though...
target_include_directories(origami PUBLIC ${INCLUDES})
target_include_directories(origami_debug PUBLIC ${INCLUDES})

target_link_libraries(origami PUBLIC ${LIBRARIES})
target_link_libraries(origami_debug PUBLIC ${LIBRARIES})
# ^ redundant, refactor please

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${BINARIES} PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

# TODO: Add tests and install targets if needed.
