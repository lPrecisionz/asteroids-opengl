# Asteroids - OpenGL

A simple asteroids clone using OpenGL.

## Description

This project is being developed after finishing the **"Getting Started"** section of [learnopengl.com](https://learnopengl.com/), with the goal of practicing real-time rendering, basic game architecture, and OpenGL fundamentals.

## Getting Started

### Dependencies

You’ll need the following installed:

- **C++20 compatible compiler** (GCC / Clang / MSVC)
- **CMake**
- **GLFW** (window + input)
- **GLAD** (OpenGL loader)
- **GLM** (math library)

### Installing

1. Clone the repository:
```bash
git clone <https://github.com/lPrecisionz/asteroids-opengl.git
cd asteroids-opengl
```
2. Ensure all dependencies are installed and available.
- GLFW must be installed system-wide.
- GLM must be installed system-wide.
- GLAD's single header file is already included in 'external/glad'

### Executing

```bash
cmake -S . -B build
cmake --build build
./build/Asteroids
```

###License

This project is for learning purposes. Feel free to fork and modify it. 
