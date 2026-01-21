#pragma once
#include "model.hpp"
#include <vector>

const float player_model [] = {
   0.0f,   0.1f, 0.0f, // top
  -0.05f,  -0.1f, 0.0f, // bottom-left
   0.0f,   0.1f, 0.0f, // top
   0.05f,  -0.1f, 0.0f,  // bottom-right
   -0.035f, -0.04f, 0.0f, 
   0.035f,  -0.04f, 0.0f
  //-0.7f,   0.0f, 0.0f, 
   //0.7f,   0.0f, 0.0f
};

const std::vector<vertex_attr_data> player_vertex_attr {
  vertex_attr_data(GL_FLOAT, 0, 3, 0) // type -> location -> attr count -> offset
};

const mesh_data player_mesh = {
  // arr -> arr_size -> stride -> draw_kind -> vertice_count
  mesh_data(player_model, 
            sizeof(float) * 18, 
            sizeof(float) * 3, 
            GL_STATIC_DRAW, 
            6
  ) 
};
/*
struct mesh_data {
  const float* vertex_arr; 
  const size_t arr_size; 
  const size_t stride;
  const GLenum draw_kind;
  const unsigned int vertice_count;
};*/
