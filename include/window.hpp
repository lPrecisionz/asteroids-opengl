#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Asteroids{

class WindowManager{
private: 
  const unsigned int m_version;
  const unsigned int m_width;
  const unsigned int m_height;
  GLFWwindow *m_window;
  const char *m_window_name;

public: 
  WindowManager(int version, int width, int height, const char* window_name);
  ~WindowManager();
  GLFWwindow *get_window() { return m_window; }
  void swap_buffer() { glfwSwapBuffers(m_window);}
  void poll_events() { glfwPollEvents(); }
  void clear_color(const float r, const float g, const float b, const float a);
  static void framebuffer_size_callback(GLFWwindow *window, int width, int height){ glViewport(0, 0, width, height); }

};

} // namespace Asteroids
