#include "../include/game.hpp"
#include "../models/player_model.hpp"
#include "../models/projectile_model.hpp"
#include "../models/asteroids.hpp"
#include "../include/renderer.hpp"
#include "entity.hpp"
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
    renderer.draw_scene(m_entities, *m_player);

    handle_input(delta_time);
    update_entities(delta_time);
    asteroid_player_coll();
    asteroid_proj_coll();
    cleanup_entities();

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
    m_entities.push_back(
      std::unique_ptr<Projectile>(new Projectile(spawn_proj()))
    );
  }
  if(glfwGetKey(m_window_manager.get_window(), GLFW_KEY_E) == GLFW_PRESS){
    m_entities.push_back(
      std::unique_ptr<Enemy>(new Enemy(spawn_enemy()))
    );
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
  point player_pos = {0, 0};
  point player_vel = {0, 0};
  float player_angle = 0.0f; 
  float player_scale = 1.0f;
  std::string player_mesh {"Ship"};

  return Player(player_pos, player_vel, player_mesh, player_scale, player_angle);
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

    Entity health_ship = Player(bar_pos, bar_vel, bar_mesh, bar_scale, bar_angle);
    health_ship.m_scale = 0.5f;
    m_entities.push_back(
      std::unique_ptr<Entity>(new Player(bar_pos, bar_vel, bar_mesh, bar_scale, bar_angle))
    );
  }
}

void Game::update_entities(const float &dt){
  for(auto &e : m_entities){
    e->update(dt);
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
  std::vector<Entity*> asteroids;
  for(auto&e : m_entities){
    float curr_distance = sqrt(pow(m_player->m_pos.x - e->m_pos.x,2) + pow(m_player->m_pos.y - e->m_pos.y,2));
    if(curr_distance < m_player->m_radius)
      std::cout << "Collision!" << std::endl;
  }
}

void Game::asteroid_proj_coll(){
  std::vector<Entity*> asteroids;  
  std::vector<Entity*> projectiles;

  for(auto &e : m_entities){
    switch(e->m_id){
      case EntityID::ENEMY: 
        asteroids.push_back(e.get());
        break;
      case EntityID::PROJECTILE: 
        projectiles.push_back(e.get());
        break;
      default:
        continue;
    }
  }

  for(auto &ast : asteroids){
    for(auto &proj: projectiles){
      float curr_distance = sqrt(pow(ast->m_pos.x - proj->m_pos.x,2) + pow(ast->m_pos.y - proj->m_pos.y,2));
      if(curr_distance < ast->m_radius){
        std::cout << "bullet hit!" << std::endl;
      } 
    }
  }
}

} // namespace Asteroids
