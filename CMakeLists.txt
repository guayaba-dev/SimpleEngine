cmake_minimum_required(VERSION 3.16)

project(GameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=undefined -g -O0 -Wall)
    add_link_options(-fsanitize=undefined)
else()
    add_compile_options(-O2 -Wall -Wextra)
endif()

find_package(OpenGL REQUIRED)
find_package(GLFW 3.3 QUIET)


# Core library
add_subdirectory(core)
# Vendor library
add_subdirectory(vendor)


# OpenGL + GLFW

# App executable
add_executable(${PROJECT_NAME}_app app.cpp)

target_link_libraries(
    ${PROJECT_NAME}_app
    PUBLIC 
        vendor
        core
        GL
        glfw
)

