#pragma once
#include "model.hpp"
#include <vector> 

const float projectile_model [] = {
  -0.1f,  0.1f, 0.0f, // top left
   0.1f,  0.1f, 0.0f, // top right
   0.1f, -0.1f, 0.0f, // bottom right
  -0.1f, -0.1f, 0.0f  // bottom left
};

const std::vector<vertex_attr_data> player_vertex_attr {
  vertex_attr_data(GL_FLOAT, 0, 3, 0) // type -> location -> attr count -> offset
};

const mesh_data player_mesh = {
  mesh_data(projectile_model, 
            sizeof(float) * 12, 
            sizeof(float) * 3, 
            GL_STATIC_DRAW, 
            GL_LINES,
            4
  ) 
};

