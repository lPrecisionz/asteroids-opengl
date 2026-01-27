#include "../include/game.hpp"
#include "../models/player_model.hpp"
#include "../models/projectile_model.hpp"
#include "../models/asteroids.hpp"
#include "../include/renderer.hpp"
#include "entity.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Asteroids{

void Game::run(){
  Renderer renderer {m_meshes, m_shader};

  Player player = spawn_player();
  m_player = &player;
  spawn_health_bar();

  float prev_frame {0};
  while(!m_window_manager.window_should_close()){
    float curr_frame = glfwGetTime();
    m_delta_time = curr_frame - prev_frame;
    prev_frame = curr_frame;

    m_window_manager.clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    m_shader.use();
    renderer.draw_scene(m_entities, *m_player);

    m_player->handle();
    update_entities();
    asteroid_player_coll();
    asteroid_proj_coll();
    cleanup_entities();

    m_window_manager.swap_buffer();
    m_window_manager.poll_events();
  }
}

void Game::set_input_callback(){
  GLFWwindow *window = m_window_manager.get_window();
  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
    Game *game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    game->handle_input(window, key, scancode, action, mods);
  });
}

void Game::handle_input(GLFWwindow* window, int key, int scancode, int action, int mods){
  //TODO : Clean up this mess
  switch(key){
    case GLFW_KEY_LEFT:
      if(action == GLFW_PRESS)
        m_player->set_state(PlayerState::SPIN_LEFT);
      else if (action == GLFW_RELEASE && m_player->m_state == PlayerState::SPIN_LEFT)
       m_player->set_state(PlayerState::IDLE);
      break;
    case GLFW_KEY_RIGHT:
      if(action == GLFW_PRESS)
        m_player->set_state(PlayerState::SPIN_RIGHT);
      else if (action == GLFW_RELEASE && m_player->m_state == PlayerState::SPIN_RIGHT)
        m_player->set_state(PlayerState::IDLE);      
      break;
    case GLFW_KEY_SPACE:
      if(action == GLFW_PRESS)
        m_entities.push_back( 
          std::unique_ptr<Projectile>(new Projectile(spawn_proj()))
        );
      break;
    case GLFW_KEY_E:
      if(action == GLFW_PRESS)
        m_entities.push_back(
          std::unique_ptr<Enemy>(new Enemy(spawn_enemy()))
        );
      break;
  }
}

void Game::init_mesh_map(){
  m_meshes = { 
    { "Ship",       Mesh(player_mesh    , player_vertex_attr)   },
    { "Projectile", Mesh(proj_mesh      , proj_vert_attr)       }, 
    { "Asteroid01", Mesh(asteroid01_mesh, asteroid01_vertex_arr)}
  };
}

Player Game::spawn_player(){

  const float spin_speed = 0.5f;
  point player_pos = {0, 0};
  point player_vel = {0, 0};
  float player_angle = 0.0f; 
  float player_scale = 1.0f;
  std::string player_mesh {"Ship"};

  return Player(player_pos, player_vel, player_mesh, player_scale, player_angle, spin_speed);
}

Projectile Game::spawn_proj(){
  float ship_height = (SHIP_HEIGHT * m_player->m_scale) / 2.0f;
  float proj_angle = m_player->m_angle + PLAYER_OFFSET_ANGLE; 
  float proj_scale = 0.05f;
  std::string proj_mesh {"Projectile"};

  const float vel_x = cos(glm::radians(proj_angle)), 
              vel_y = sin(glm::radians(proj_angle)), 
              speed = PROJ_SPEED;

  point proj_vel = {vel_x * speed, vel_y * speed};
  point proj_pos = point(vel_x * ship_height, vel_y * ship_height);

  return Projectile(proj_pos, proj_vel, proj_mesh, proj_scale, proj_angle);
}

Enemy Game::spawn_enemy(){
  float enemy_angle = m_random_engine.random_angle();
  float enemy_scale = m_random_engine.random_scale();
  std::string enemy_mesh {"Asteroid01"};

  const float vel_x = cos(glm::radians(enemy_angle)), 
              vel_y = sin(glm::radians(enemy_angle)), 
              speed = 0.01;
  point enemy_vel = {vel_x * speed, vel_y * speed};
  point enemy_pos = {m_random_engine.random_outside_coord(), m_random_engine.random_outside_coord()}; 

  return Enemy(enemy_pos, enemy_vel, enemy_mesh, enemy_scale, enemy_angle);
}

void Game::spawn_health_bar(){
  const unsigned int health_count { 3 };
  const float health_padding {0.075f}, 
              bar_xstart     {-0.95}, 
              bar_ystart     { 0.9 }, 
              bar_angle      {0.0f}, 
              bar_scale      {0.5f};

  for(int i = 0; i < health_count; ++i){
    float curr_x = bar_xstart + (i * health_padding);

    point bar_pos = {curr_x, bar_ystart};
    point bar_vel = {0, 0};
    std::string bar_mesh {"Ship"};

    Entity health_ship = Entity(bar_pos, bar_vel, bar_mesh, bar_scale, bar_angle);
    health_ship.m_scale = 0.5f;
    m_entities.push_back(
      std::unique_ptr<Entity>(new Entity(bar_pos, bar_vel, bar_mesh, bar_scale, bar_angle))
    );
  }
}

void Game::update_entities(){
  for(auto &e : m_entities){
    e->update(m_delta_time);
  }
}

void Game::cleanup_entities(){
  for(size_t i = 0; i < m_entities.size(); ++i){
    if(m_entities.at(i)->m_should_destroy)
      m_entities.erase(m_entities.begin() + i);
  }
}

std::vector<Entity*> Game::cache_entities(const EntityID &type){
  std::vector<Entity*> cached_entities; 
  for(auto& e : m_entities){
    if(e->m_id == type)
      cached_entities.push_back(e.get());
  }
  return cached_entities;
}

void Game::asteroid_player_coll(){
  std::vector<Entity*> asteroids = cache_entities(EntityID::ENEMY);
  for(auto&e : asteroids){
    if(check_coll(m_player->m_radius, m_player->m_pos, e->m_pos))
      std::cout << "Collision!" << std::endl;
  }
}

void Game::asteroid_proj_coll(){
  std::vector<Entity*> asteroids = cache_entities(EntityID::ENEMY);  
  std::vector<Entity*> projectiles = cache_entities(EntityID::PROJECTILE);

  for(auto &ast : asteroids){
    for(auto &proj: projectiles){
      if(check_coll(ast->m_radius, ast->m_pos, proj->m_pos)){
        std::cout << "bullet hit!" << std::endl;
      } 
    }
  }
}

bool Game::check_coll(const float &radius_a, const point &a, const point &b) const{
  float distance = sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
  return distance < radius_a;
}

bool Enemy::die(){
  m_state = EnemyState::DEAD;
  return m_scale > 0.5f;
}

} // namespace Asteroids
