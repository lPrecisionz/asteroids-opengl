#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "window.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace Asteroids{

class Shader{
public:
  unsigned int m_id;

public:
  Shader(const char* vertex_path, const char* fragment_path);
  void use() { glUseProgram(m_id); }
  void set_mat4fv(const char* uni_name, const glm::mat4 &matrix) const;
private:
  unsigned int m_vertex;
  unsigned int m_fragment;
  const std::string read_from_file(const char* file_path);
  void compile(GLenum shader_kind, const char* src_code); 
  void link();
};

} // namespace Asteroids
