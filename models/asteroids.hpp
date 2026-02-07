#pragma once
#include "model.hpp"
#include <vector>

const float asteroid01 [] = {
-0.1f, 0.5f, 0.0f, 
0.2f,  0.5f, 0.0f, 

0.2f,  0.5f, 0.0f,
0.5f,  0.2f, 0.0f, 

0.5f,  0.2f, 0.0f,
0.5f,  0.0f, 0.0f, 

0.5f,  0.0f, 0.0f,
0.1f, -0.5f, 0.0f, 

0.1f, -0.5f, 0.0f,
-0.1f, -0.5f, 0.0f, 

-0.1f, -0.5f, 0.0f,
-0.1f, 0.0f, 0.0f, 

-0.1f, 0.0f, 0.0f, 
-0.4f, -0.5f, 0.0f, 

-0.4f, -0.5f, 0.0f,
-0.5f, -0.1f, 0.0f,

-0.5f, -0.1f, 0.0f,
-0.3f, 0.1f, 0.0f, 

-0.3f, 0.1f, 0.0f, 
-0.5f, 0.2f, 0.0f, 

-0.5f, 0.2f, 0.0f,
-0.1f, 0.5f, 0.0f
};
// 22 vertices

const std::vector<vertex_attr_data> asteroid01_vertex_arr {
  vertex_attr_data(GL_FLOAT, ATTR_LOC, ATTR_COUNT, 0) // type -> location -> attr count -> offset
};

const mesh_data asteroid01_mesh = {
  mesh_data(asteroid01, 
            sizeof(asteroid01), 
            MESH_STRIDE, 
            GL_STATIC_DRAW, 
            GL_LINES,
            22
  ) 
};
