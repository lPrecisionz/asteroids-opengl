#include "../include/game.hpp"
#include "../models/player_model.hpp"
#include "../models/projectile_model.hpp"
#include "../include/renderer.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Asteroids{

void Game::run(){
  Renderer renderer {m_meshes, m_shader};

  Player player = spawn_player();
  m_player = &player;
  spawn_health_bar();

  float prev_frame {0}, 
        delta_time {0};
  while(!m_window_manager.window_should_close()){
    float curr_frame = glfwGetTime();
    delta_time = curr_frame - prev_frame;
    prev_frame = curr_frame;

    m_window_manager.clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    m_shader.use();
    handle_input(delta_time);
    update_entities(delta_time);
    renderer.draw_scene(m_entities, *m_player);

    m_window_manager.swap_buffer();
    m_window_manager.poll_events();
  }
}

void Game::handle_input(const float &dt){
  if(glfwGetKey(m_window_manager.get_window(), GLFW_KEY_RIGHT) == GLFW_PRESS){
    m_player->rotate(-SPIN_SPEED * dt);
  }
  if(glfwGetKey(m_window_manager.get_window(), GLFW_KEY_LEFT) == GLFW_PRESS){
    m_player->rotate(SPIN_SPEED * dt);
  }
  if(glfwGetKey(m_window_manager.get_window(), GLFW_KEY_SPACE) == GLFW_PRESS){
    Projectile p = spawn_proj();
    m_entities.push_back(p);
    std::cout << "Shot fired!" << std::endl;
  }
}

void Game::init_mesh_map(){
  m_meshes = { 
    { "Ship", Mesh(player_mesh, player_vertex_attr) },
    { "Projectile", Mesh(proj_mesh, proj_vert_attr) }
  };
}

Player Game::spawn_player(){
  point player_pos = {0, 0};
  point player_vel = {0, 0};
  float player_angle = 0.0f; 
  float player_scale = 1.0f;
  std::string player_mesh {"Ship"};

  return Player(player_pos, player_vel, player_mesh, player_scale, player_angle);
}

Projectile Game::spawn_proj(){
  // position should somewhat be offsetted since bullets shouldn't spawn at origin
  // remember to do that later
  point proj_pos = {0, 0};
  float proj_angle = m_player->m_angle + 90.0f; 
  float proj_scale = 0.05f;
  std::string proj_mesh {"Projectile"};

  const float vel_x = cos(glm::radians(proj_angle)), 
              vel_y = sin(glm::radians(proj_angle));

  std::cout << "angle : " << proj_angle << std::endl 
            << "vel x : " << vel_x << std::endl 
            << "vel y : " << vel_y << std::endl;

  const float speed = 0.01f;
  point proj_vel = {vel_x * speed, vel_y * speed};

  return Projectile(proj_pos, proj_vel, proj_mesh, proj_scale, proj_angle);
}

void Game::spawn_health_bar(){
  const unsigned int health_count { 3 };
  const float health_padding {0.075f}, 
              bar_xstart     {-0.95}, 
              bar_ystart     { 0.9 }, 
              bar_angle      {0.0f}, 
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

void Game::update_entities(const float &dt){
  for(auto &e : m_entities){
    e.move();
  }
}

} // namespace Asteroids
