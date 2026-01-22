#pragma once
#include <GLFW/glfw3.h>

struct vertex_attr_data {
  GLenum type;
  unsigned int location;
  unsigned int attr_count;
  size_t offset;
};

struct mesh_data {
  const float* vertex_arr; 
  const size_t arr_size; 
  const size_t stride;
  const GLenum draw_kind;
  const GLenum geometry_kind;
  const unsigned int vertice_count;


  /*mesh_data(const mesh_data &md)
    : vertex_arr(md.vertex_arr), 
      arr_size(md.arr_size), 
      stride(md.stride), 
      draw_kind(md.draw_kind), 
      geometry_kind(md.geometry_kind), 
      vertice_count(md.vertice_count){}
  */
};
