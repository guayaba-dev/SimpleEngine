add_library(vendor SHARED)

# GLAD source
target_sources(vendor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c
)

# Exponer headers
target_include_directories(vendor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include      # entt.hpp y stb_image.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include # glad/
        ${CMAKE_CURRENT_SOURCE_DIR}/glm          # glm/
)
