#pragma once
#include <glm/glm.hpp>

namespace Asteroids{

class Renderer{
public:
  glm::mat4 m_view; 
  glm::mat4 m_model;
  glm::mat4 m_projection;

public:
  Renderer(){}
};

} // namespace Asteroids
