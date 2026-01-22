#pragma once
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include "entity.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include <map>

namespace Asteroids{

class Renderer{
private:
  const Shader* m_shader_ref;
  glm::mat4 m_model      {glm::mat4(1.0f)};
  glm::mat4 m_view       {glm::mat4(1.0f)}; 
  glm::mat4 m_projection {glm::mat4(1.0f)};
  //glm::mat4 m_projection {glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.01f, 100.0f)};

  const std::map<std::string, Mesh>* m_mesh_ref;

public:
  Renderer(const std::map<std::string, Mesh> &meshes, const Shader &shader) 
    : m_mesh_ref(&meshes), m_shader_ref(&shader){}
  void draw(const std::vector<Entity> &entities);
};

} // namespace Asteroids
