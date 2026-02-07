#pragma once
#include "model.hpp"
#include <vector>

// The 2 bottom vertices were calculated manually using linear interpolation
const float player_model [] = {
    0.000f,   0.1f,  0.0f, // top
   -0.050f,  -0.1f,  0.0f, // bottom-left
    0.000f,   0.10f, 0.0f, // top
    0.050f,  -0.10f, 0.0f, // bottom-right
   -0.035f,  -0.04f, 0.0f, // bar-left
    0.035f,  -0.04f, 0.0f  // bar-right
};

const float SHIP_TOP    = player_model[1]; 
const float SHIP_BOTTOM = player_model[4];
const float SHIP_HEIGHT = SHIP_TOP - SHIP_BOTTOM;

const int   PLAYER_MODEL_VERTICES = 6;

const std::vector<vertex_attr_data> player_vertex_attr {
  vertex_attr_data(GL_FLOAT, ATTR_LOC, ATTR_COUNT, 0) // type -> location -> attr count -> offset
};

const mesh_data player_mesh = {
  mesh_data(player_model, 
            sizeof(player_model), 
            MESH_STRIDE, 
            GL_STATIC_DRAW, 
            DRAW_KIND,
            PLAYER_MODEL_VERTICES
  ) 
};

