add_library(core SHARED)

target_include_directories(core 
  PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(core
  PRIVATE
        src/inputManager.cpp
        src/meshManager.cpp
        src/renderer.cpp
        src/shader.cpp
        src/shaderManager.cpp
        src/textureManager.cpp
        src/window.cpp
        src/system.cpp
      )

target_precompile_headers(core 
      PUBLIC
    include/core/pch.hpp
)
      
target_link_libraries(core 
  PUBLIC
    vendor
)
