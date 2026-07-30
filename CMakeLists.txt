cmake_minimum_required(VERSION 3.16)

project(GameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_link_options(-fuse-ld=mold)

# Debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address -fsanitize=undefined -g -Wall -O0)
    add_link_options(-fsanitize=address -fsanitize=undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "fast")
    add_compile_options(-g -O0)
else()
    add_compile_options(-O0 -Wall -Wextra -g)
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

target_precompile_headers(${PROJECT_NAME}_app REUSE_FROM core)
