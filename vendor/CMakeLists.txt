add_library(vendor SHARED)

# GLAD source
target_sources(vendor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-1.92.8/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-1.92.8/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-1.92.8/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-1.92.8/imgui_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-1.92.8/imgui_impl_glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-1.92.8/imgui_impl_opengl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-1.92.8/imgui_demo.cpp
)

# Exponer headers
target_include_directories(vendor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include      # entt.hpp y stb_image.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include # glad/
        ${CMAKE_CURRENT_SOURCE_DIR}/glm          # glm/
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-1.92.8 #imgui
)
