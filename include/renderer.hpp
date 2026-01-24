#pragma once
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include "entity.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "player.hpp"
#include <memory>
#include <map>

namespace Asteroids{

class Renderer{
private:
  const Shader* m_shader_ref;
  glm::mat4 m_model      {glm::mat4(1.0f)};
  glm::mat4 m_view       {glm::mat4(1.0f)}; 
  glm::mat4 m_projection {glm::mat4(1.0f)};

  const std::map<std::string, Mesh>* m_mesh_ref;

public:
  Renderer(const std::map<std::string, Mesh> &meshes, const Shader &shader) 
    : m_mesh_ref(&meshes), m_shader_ref(&shader){}
  void draw_scene(const std::vector<std::unique_ptr<Entity>> &entities, const Player& p);

private:
  void draw_entities(const std::vector<std::unique_ptr<Entity>> &entities);
  void draw_player(const Player& p);
};

} // namespace Asteroids
