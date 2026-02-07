#pragma once
#include "model.hpp"
#include <vector> 

const float projectile_model [] = {
  -0.1f,  0.1f, 0.0f,  // top left
   0.1f,  0.1f, 0.0f,  // top right
  
   0.1f,  0.1f, 0.0f,  // top right
   0.1f, -0.1f, 0.0f,  // bottom right
  
   0.1f, -0.1f, 0.0f,  // bottom right
  -0.1f, -0.1f, 0.0f,  // bottom left
  
  -0.1f, -0.1f, 0.0f,  // bottom left
  -0.1f,  0.1f, 0.0f   // top left
};

const float PROJ_MESH_HEIGHT   = 0.2;
const int   PROJ_MESH_VERTICES = 8;

const std::vector<vertex_attr_data> proj_vert_attr {
  vertex_attr_data(GL_FLOAT, ATTR_LOC, ATTR_COUNT, 0) // type -> location -> attr count -> offset
};

const mesh_data proj_mesh = {
  mesh_data(projectile_model, 
            sizeof(projectile_model), 
            MESH_STRIDE, 
            GL_STATIC_DRAW, 
            DRAW_KIND,
            PROJ_MESH_VERTICES
  ) 
};
