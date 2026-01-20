#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Asteroids{

class Window{
public: 
  const unsigned int m_version;
  const unsigned int m_width;
  const unsigned int m_height;
  GLFWwindow *m_window;
  const char *m_window_name;

public: 
  Window(int version, int width, int height, const char* window_name);
  ~Window();
  static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};

} // namespace Asteroids
