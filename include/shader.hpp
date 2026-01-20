#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "window.hpp"
namespace Asteroids{

class Shader{
public:
  unsigned int m_id;

public:
  Shader(const char* vertex_path, const char* fragment_path);
  void use() { glUseProgram(m_id); }
private:
  unsigned int m_vertex;
  unsigned int m_fragment;
  const std::string read_from_file(const char* file_path);
  void compile(GLenum shader_kind, const char* src_code); 
  void link();
};

} // namespace Asteroids
