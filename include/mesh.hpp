#pragma once
#include "window.hpp"
#include <vector>
#include "../models/model.hpp"

namespace Asteroids{

class Mesh{
private: 
  unsigned int m_VAO; 
  unsigned int m_VBO;
  unsigned int m_vertice_count;
  mesh_data m_data;

public: 
  Mesh(const mesh_data md, const std::vector<vertex_attr_data> &attr_data); 
  void bind();
  void draw();

private: 
  void init_vao();
  void init_vbo(const mesh_data &md, const std::vector<vertex_attr_data> &attr_data);
};

} // namespace asteroids
