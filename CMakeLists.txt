cmake_minimum_required(VERSION 3.16)
project(Asteroids LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLAD (GLAD1 generated sources)
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)

# If you get linker errors related to dlopen/dlsym, keep this.
target_link_libraries(glad PUBLIC dl)

add_executable(Asteroids
    src/main.cpp
    src/window.cpp
    src/game.cpp
    src/shader.cpp
    src/mesh.cpp
    src/error.cpp
    src/renderer.cpp
    src/player.cpp
)

target_include_directories(Asteroids PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(glfw3 3.3 QUIET)

# GLM
find_package(glm CONFIG REQUIRED)

if (glfw3_FOUND)
    target_link_libraries(Asteroids PRIVATE glad glfw OpenGL::GL glm::glm)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)
    target_link_libraries(Asteroids PRIVATE glad PkgConfig::GLFW OpenGL::GL glm::glm)
endif()

