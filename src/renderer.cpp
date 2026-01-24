#include "../include/renderer.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "error.hpp"

namespace Asteroids{

void Renderer::draw_scene(const std::vector<std::unique_ptr<Entity>> &entities, const Player& p){
  draw_player(p);
  draw_entities(entities);
}

void Renderer::draw_entities(const std::vector<std::unique_ptr<Entity>> &entities){
  for(const auto& e : entities){
    const Mesh &current_mesh = m_mesh_ref->at(e->m_mesh_id);
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, glm::vec3(e->m_pos.x, e->m_pos.y, 0.0f));
    m_model = glm::scale(m_model, glm::vec3(e->m_scale, e->m_scale, e->m_scale));
    m_model = glm::rotate(m_model, glm::radians(e->m_angle), glm::vec3(0.0f, 0.0f, 1.0f));
    m_shader_ref->set_mat4fv("model", m_model);
    m_shader_ref->set_mat4fv("view", m_view);
    m_shader_ref->set_mat4fv("projection", m_projection);
    current_mesh.draw();
  }
}

void Renderer::draw_player(const Player& p){
  const Mesh &player_mesh = m_mesh_ref->at(p.m_mesh_id);
  m_model = glm::mat4(1.0f);
  m_model = glm::translate(m_model, glm::vec3(p.m_pos.x, p.m_pos.y, 0.0f));
  m_model = glm::scale(m_model, glm::vec3(p.m_scale, p.m_scale, p.m_scale));
  m_model = glm::rotate(m_model, glm::radians(p.m_angle), glm::vec3(0.0f, 0.0f, 1.0f)); 
  m_shader_ref->set_mat4fv("model", m_model);
  m_shader_ref->set_mat4fv("view", m_view);
  m_shader_ref->set_mat4fv("projection", m_projection);
  player_mesh.draw();
}

} // namespace Asteroids
