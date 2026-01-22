#include "../include/game.hpp"
#include "../include/shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Asteroids{

void Game::run(){
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view  = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  //ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
  m_shader.use();
  while(!m_window_manager.window_should_close()){
    m_window_manager.clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    handle_input(model);

    m_shader.set_mat4fv("model", model);
    m_shader.set_mat4fv("view", view);
    m_shader.set_mat4fv("projection", projection);

    m_shader.use();
    m_player.draw();
    m_window_manager.swap_buffer();
    m_window_manager.poll_events();
  }
}

void Game::handle_input(glm::mat4 &model){
  if(glfwGetKey(m_window_manager.get_window(), GLFW_KEY_RIGHT) == GLFW_PRESS){
    model = glm::rotate(model, glm::radians(-SPIN_SPEED), glm::vec3(0.0f, 0.0f, 1.0f));
  }
  if(glfwGetKey(m_window_manager.get_window(), GLFW_KEY_LEFT) == GLFW_PRESS){
    model = glm::rotate(model, glm::radians(SPIN_SPEED), glm::vec3(0.0f, 0.0f, 1.0f));
  }
}

void Game::init_mesh_map(){
  m_meshes = { 
    {"Player", Mesh(player_mesh, player_vertex_attr)}
  };
}

} // namespace Asteroids
