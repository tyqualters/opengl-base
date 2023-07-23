cmake_minimum_required(VERSION 3.20)
project(opengl-project)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall -Wextra -march=native")

add_executable(${PROJECT_NAME}
    src/main.cc
    src/buffer_layout.cc
    src/ibo.cc
    src/program.cc
    src/renderer.cc
    src/stb_image.c
    src/texture.cc
    src/vao.cc
    src/vbo.cc
    src/cube.cc
    src/glad.c
)

# Find packages
find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
  ${GLM_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS}
  include/
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES} ${OPENGL_LIBRARY}
)

# Post-build copy shaders to output directory
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${PROJECT_SOURCE_DIR}/shaders 
    ${PROJECT_BINARY_DIR}/shaders)

add_custom_target(foo DEPENDS ${PROJECT_SOURCE_DIR}/shaders)
add_dependencies(${PROJECT_NAME} foo)