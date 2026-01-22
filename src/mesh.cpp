#include "../include/mesh.hpp"
#include "../include/error.hpp"
#include <iostream>

namespace Asteroids{

Mesh::Mesh(const mesh_data md, const std::vector<vertex_attr_data> &attr_data) : m_data(md){
  init_vao();
  init_vbo(md, attr_data);
  m_vertice_count = md.vertice_count;
}

void Mesh::bind() const{
  glBindVertexArray(m_VAO);
}

void Mesh::draw() const{
  bind();
  glDrawArrays(m_data.geometry_kind, 0, m_vertice_count);
}

void Mesh::init_vao(){
  unsigned int vao_count { 1 };
  glGenVertexArrays(vao_count, &m_VAO);
  std::cout << "Generated VAO id: " << m_VAO << std::endl;
}

void Mesh::init_vbo(const mesh_data &md, const std::vector<vertex_attr_data> &attr_data){
  bind();
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, md.arr_size, md.vertex_arr, md.draw_kind);

  GLenum normalize_flag = GL_FALSE;
  for(auto i : attr_data){
    glVertexAttribPointer(i.location, i.attr_count, i.type, normalize_flag, md.stride, (void*)i.offset);
    glEnableVertexAttribArray(i.location);
  }
  std::cout << "Generated and binded VBO id: " << m_VBO << std::endl;
}

} // namespace Asteroids
