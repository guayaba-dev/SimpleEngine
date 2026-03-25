cmake_minimum_required(VERSION 3.16)

project(GameEngine)

set(CMAKE_CXX_STANDARD 17)          
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

find_package(OpenGL REQUIRED)
find_package(GLFW 3.3 REQUIRED)

file(GLOB CORE_FILES core/*.cpp core/*.c)
add_library(CORE_lib ${CORE_FILES})

add_executable(${PROJECT_NAME}_app app.cpp)

target_link_libraries(
  ${PROJECT_NAME}_app 
  PRIVATE
  GL
  GLFW
  CORE_lib
)


