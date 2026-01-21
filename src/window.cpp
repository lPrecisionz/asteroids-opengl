#include "../include/window.hpp"

namespace Asteroids{

WindowManager::WindowManager(int version, int width, int height, const char* window_name) : m_version(version), m_width(width), m_height(height), m_window_name(window_name){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_version);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_version);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(m_width, m_height, m_window_name, NULL, NULL);
  if(m_window == NULL)
    throw std::runtime_error("Couldn't initialize window");
  
  glfwMakeContextCurrent(m_window);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Couldn't initialize GLAD");

  glViewport(0, 0, m_width, m_height);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void WindowManager::clear_color(const float r, const float g, const float b, const float a){
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(r, g, b, a);
}

WindowManager::~WindowManager(){
  glfwTerminate();
}


} // namespace lPrecisionz
