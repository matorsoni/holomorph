cmake_minimum_required(VERSION 3.8)

project(holomorph)

add_executable(
    app
        src/main.cpp
        deps/glad/src/gl.c
)

add_subdirectory(
    deps/glfw
)

target_include_directories(
    app
    PRIVATE
        deps/glad/include
        deps/glfw/include
)

target_link_libraries(
    app
    glfw
)
