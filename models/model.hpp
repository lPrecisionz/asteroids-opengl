#pragma once
#include <GLFW/glfw3.h>

struct vertex_attr_data {
  GLenum type;
  unsigned int location, 
               attr_count;
  size_t offset;
};

struct mesh_data {
  const float* vertex_arr; 
  const size_t arr_size; 
  const size_t stride;
  const GLenum draw_kind;
};
