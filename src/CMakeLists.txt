# CMakeList.txt : CMake project for origami, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(GLFW_PATH "../deps/glfw-3.2.1")
set(RES_PATH "../res")
set(GLAD "${GLFW_PATH}/deps/glad/glad.h" "${GLFW_PATH}/deps/glad.c")

FILE(GLOB ORIGAMI *.c)
# set(ORIGAMI "app.c" "device_interface.c" "file_utils.c" "main.c" "tuple_interface.c" "utils.c")
set(SHADERS "${RES_PATH}/shaders/default.vsh" "${RES_PATH}/shaders/default.fsh")

find_library(GLFW_LIB glfw3 HINTS "${GLFW_PATH}/lib-vc2015")
link_directories("${GLFW_PATH}/lib-vc2015")

# Add source to this project's executable.
add_executable (origami WIN32 ${ORIGAMI} ${SHADERS} "${GLFW_PATH}/include/GLFW/glfw3.h" ${GLAD})

# Build without console
add_executable (origami_debug ${ORIGAMI} ${SHADERS} "${GLFW_PATH}/include/GLFW/glfw3.h" ${GLAD})

set(BINARIES origami origami_debug)
set(INCLUDES "${GLFW_PATH}/include/" "${GLFW_PATH}/deps/" "${RES_PATH}")
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
