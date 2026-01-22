#include "../include/renderer.hpp"
#include <glm/ext/matrix_transform.hpp>

namespace Asteroids{

void Renderer::draw(const std::vector<Entity> &entities){
  for(const auto& e : entities){
    const Mesh &current_mesh = m_mesh_ref->at(e.m_mesh_id);
    m_model = glm::translate(m_model, glm::vec3(e.m_pos.x, e.m_pos.y, 1.0f));
    m_shader_ref->set_mat4fv("model", m_model);
    current_mesh.draw();
  }
}


} // namespace Asteroids
