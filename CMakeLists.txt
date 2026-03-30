cmake_minimum_required(VERSION 3.16)

project(GameEngine)

set(CMAKE_CXX_STANDARD 17)          
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

find_package(OpenGL REQUIRED)
find_package(GLFW 3.3 QUIET)

add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
add_link_options(-fsanitize=address,undefined -fno-omit-frame-pointer)

file(GLOB CORE_FILES core/*.cpp core/*.c)
file(GLOB_RECURSE VENDOR_FILES vendor/*.cpp vendor/*.c)
add_library(CORE_lib ${CORE_FILES})
add_library(VENDOR_lib ${VENDOR_FILES})

target_include_directories(CORE_lib PUBLIC core)
target_include_directories(VENDOR_lib PUBLIC vendor)

add_executable(${PROJECT_NAME}_app app.cpp)

target_link_libraries(
  ${PROJECT_NAME}_app 
  PRIVATE
  GL
  glfw 
  CORE_lib
  VENDOR_lib
)


