#pragma once
#include "model.hpp"
#include <vector>

const float player_model [] = {
   0.0f,  0.1f, 1.0f, // top
  -0.9f, -0.9f, 1.0f, // bottom-left
   0.1f,  0.1f, 1.0f  // bottom-right
};

const std::vector<vertex_attr_data> player_vertex_attr {
  vertex_attr_data(GL_FLOAT, 0, 3, 0) // type -> location -> attr count -> offset
};

const mesh_data player_mesh = {
  mesh_data(player_model, 3, sizeof(float) * 6, GL_DYNAMIC_DRAW, 6) // arr -> attr_count -> stride -> draw kind -> vert count
};
