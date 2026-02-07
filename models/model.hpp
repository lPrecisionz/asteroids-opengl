#pragma once
#include <GLFW/glfw3.h>

constexpr int    ATTR_COUNT  = 3;
constexpr size_t MESH_STRIDE = ATTR_COUNT * sizeof(float);
constexpr GLenum DRAW_KIND   = GL_LINES;
constexpr int    ATTR_LOC    = 0;

struct vertex_attr_data {
  GLenum       type;
  unsigned int location;
  unsigned int attr_count;
  size_t       offset;
};

struct mesh_data {
  const float* vertex_arr; 
  const size_t arr_size; 
  const size_t stride;
  const GLenum draw_kind;
  const GLenum geometry_kind;
  const unsigned int vertice_count;
};
