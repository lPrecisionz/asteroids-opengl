#include "../include/game.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ostream>

namespace Asteroids{

void Game::run(){
  Renderer renderer {m_meshes, m_shader};

  /*glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view  = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
  */
  spawn_player();
  spawn_health_bar();
  while(!m_window_manager.window_should_close()){
    m_window_manager.clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    //handle_input(model);
    /*m_shader.use();
    m_shader.set_mat4fv("model", model);
    m_shader.set_mat4fv("view", view);
    m_shader.set_mat4fv("projection", projection);
    m_shader.use();
    m_player.draw();
    */
    m_shader.use();
    renderer.draw(m_entities);
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
    {"Ship", Mesh(player_mesh, player_vertex_attr)}
  };
}

void Game::spawn_player(){
  point player_pos = {0, 0};
  point player_vel = {0, 0};
  float player_angle = 90.0f; 
  float player_scale = 1.0f;
  std::string player_mesh {"Ship"};

  Player player = Player(player_pos, player_vel, player_mesh, player_scale, player_angle);
  m_entities.push_back(player);
}

void Game::spawn_health_bar(){
  const unsigned int health_count { 3 };
  const float health_padding {0.1f}, 
              bar_xstart     {-0.95}, 
              bar_ystart     {0.9}, 
              bar_angle      {90.0f}, 
              bar_scale      {0.8f};

  for(int i = 0; i < health_count; ++i){
    float curr_x = bar_xstart + (i * health_padding);

    point bar_pos = {curr_x, bar_ystart};
    point bar_vel = {0, 0};
    std::string bar_mesh {"Ship"};

    Entity health_ship = Player(bar_pos, bar_vel, bar_mesh, bar_scale, bar_angle);
    health_ship.m_scale = 0.5f;
    m_entities.push_back(health_ship);
  }
}

} // namespace Asteroids
