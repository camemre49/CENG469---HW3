cmake_minimum_required(VERSION 3.30)
project(hw3)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(hw3 src/main.cpp
        headers/particle.h
        headers/window.h
        headers/base.h
        src/window.cpp
        src/callbacks.cpp
        headers/callbacks.h
        src/particle.cpp
        src/shaders.cpp
        headers/shaders.h)

# Link OpenGL, GLEW, and GLFW to the target executable
target_link_libraries(hw3 OpenGL::GL GLEW::GLEW glfw)