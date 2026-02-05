#include "../include/game.hpp"
#include "../models/player_model.hpp"
#include "../include/renderer.hpp"
#include "entity.hpp"
#include "projectile.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Asteroids{

void Game::run(){
  Renderer renderer {
    m_entity_manager.m_meshes, 
    m_shader
  };

  float prev_frame{0};
  while(!m_window_manager.window_should_close()){
    m_window_manager.poll_events();

    float curr_frame = glfwGetTime();
    m_delta_time     = curr_frame - prev_frame;
    prev_frame       = curr_frame;

    handle_state();

    m_window_manager.clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    m_shader.use();
    renderer.draw_scene(m_entity_manager.m_entities, m_entity_manager.m_player);

    m_window_manager.swap_buffer();
    m_input_handler.free_keys();
  }
}

void Game::handle_state(){
  switch(m_state){
    case GameState::MAIN_MENU:
      main_menu();
    break;
    case GameState::GAMEPLAY:
      gameplay();
    break;
    case GameState::GAMEOVER:
      game_over();
    break;
  }
}

void Game::set_state(const GameState s){
  m_state = s;
}

void Game::main_menu(){
  enemy_spawner();
  control_menu();
}

void Game::gameplay(){
    enemy_spawner();

    if(!m_entity_manager.player_active()){
      death_cooldown();
    }
    
    m_entity_manager.update_entities(m_delta_time);
    m_entity_manager.cleanup_entities();
    control_player();

    asteroid_proj_coll();
    asteroid_player_coll();
}

void Game::game_over(){
  enemy_spawner();
  m_entity_manager.update_entities(m_delta_time);
  m_entity_manager.cleanup_entities();
  control_menu();
}

void Game::restart(){
  m_entity_manager.respawn_player();
  m_entity_manager.clear_entities();
  m_time_contr.reset();
  m_conf.reset();
}

void Game::set_input_callback(){
  GLFWwindow *window = m_window_manager.get_window();
  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
    Game *game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    game->handle_input(window, key, scancode, action, mods);
  });
}

// This function is soon to be abstracted from this class. 
void Game::handle_input(GLFWwindow* window, int key, int scancode, int action, int mods){
  switch(key){
    case GLFW_KEY_LEFT:
      if(action == GLFW_PRESS){
        m_input_handler.left_arrow.pressed = true;
        m_input_handler.left_arrow.down = true;
      }
      else if (action == GLFW_RELEASE){
        m_input_handler.left_arrow.released = true;
        m_input_handler.left_arrow.down = false;
      }
      break;
    case GLFW_KEY_RIGHT:
      if(action == GLFW_PRESS){
        m_input_handler.right_arrow.pressed = true;
        m_input_handler.right_arrow.down = true;
      }
      else if (action == GLFW_RELEASE){
        m_input_handler.right_arrow.released = true;
        m_input_handler.right_arrow.down = false;
      }
      break;
    case GLFW_KEY_SPACE:
      if(action == GLFW_PRESS){
        m_input_handler.space_bar.pressed = true;
      }
      else if (action == GLFW_RELEASE){
        m_input_handler.space_bar.released = true;
        m_input_handler.space_bar.down = false;
      }
      break;
    default:
      return;
  }
}

void Game::control_menu(){
  if(m_input_handler.space_bar.pressed){
    restart();
    set_state(GameState::GAMEPLAY);
    m_entity_manager.m_player.set_state(PlayerState::IDLE);
    spawn_health_bar(); 
  }
}

void Game::control_player(){
  if(!m_entity_manager.player_active()) return;

  if(m_input_handler.left_arrow.down)
    m_entity_manager.m_player.set_state(PlayerState::SPIN_LEFT);
  if(m_input_handler.right_arrow.down)
    m_entity_manager.m_player.set_state(PlayerState::SPIN_RIGHT);

  if(m_input_handler.left_arrow.released)
    m_entity_manager.m_player.set_state(PlayerState::IDLE);
  if(m_input_handler.right_arrow.released)
    m_entity_manager.m_player.set_state(PlayerState::IDLE);

  if(m_input_handler.space_bar.pressed){
    auto proj = create_proj();
    m_entity_manager.spawn_entity(
      proj
    );
  }
  m_entity_manager.m_player.handle(m_delta_time);
}

Player Game::spawn_player(){
  point player_pos   = {0, 0};
  point player_vel   = {0, 0};

  float spin_speed   = 230.0f;
  float player_angle = 0.0f; 
  float player_scale = 1.0f;
  std::string player_mesh {"Ship"};

  return Player(player_pos, player_vel, player_mesh, player_scale, player_angle, spin_speed);
}

std::unique_ptr<Entity> Game::create_proj(){
  float ship_height = (SHIP_HEIGHT * m_entity_manager.m_player.m_scale) / 2.0f;
  float proj_angle = m_entity_manager.m_player.m_angle + PLAYER_OFFSET_ANGLE; 
  float proj_scale = 0.05f;
  std::string proj_mesh {"Projectile"};

  const float vel_x = cos(glm::radians(proj_angle)), 
              vel_y = sin(glm::radians(proj_angle)), 
              speed = PROJ_SPEED;

  point proj_vel = {vel_x * speed, vel_y * speed};
  point proj_pos = point(vel_x * ship_height, vel_y * ship_height);

  return std::unique_ptr<Projectile>(
    new Projectile(proj_pos, proj_vel, proj_mesh, proj_scale, proj_angle, EntityID::PROJECTILE, PROJ_MAX_DIST)
  );
}

std::unique_ptr<Entity> Game::create_enemy(){
  float enemy_angle = m_random_engine.random_angle();
  float enemy_scale = m_random_engine.random_scale();
  unsigned int split_count = 0;
  std::string enemy_mesh {"Asteroid01"};

  const float vel_x = cos(glm::radians(enemy_angle)), 
              vel_y = sin(glm::radians(enemy_angle)), 
              speed = 0.5f;
  point enemy_vel = {vel_x * speed, vel_y * speed};
  point enemy_pos = {m_random_engine.random_outside_coord(), m_random_engine.random_outside_coord()}; 

  return std::unique_ptr<Enemy>(
    new Enemy(enemy_pos, enemy_vel, enemy_mesh, enemy_scale, enemy_angle, split_count)
  );
}

void Game::explode(const point &pos, const float &scale){
  std::string particle_mesh {"Projectile"};
  int particle_count = static_cast<int>(scale * 20);
  float particle_scale = 0.01f, 
        max_distance   = 0.5f;
  for(int i = 0; i < particle_count; ++i){
    float particle_angle = m_random_engine.random_angle();
    const float vel_x = cos(glm::radians(particle_angle)), 
                vel_y = sin(glm::radians(particle_angle)), 
                speed = 0.5f;
    point vel = {vel_x * speed, vel_y * speed};
    std::unique_ptr<Entity> particle = std::unique_ptr<Projectile>(
      new Projectile(pos, vel, particle_mesh, particle_scale, particle_angle, EntityID::PARTICLE, max_distance)
    );
    m_entity_manager.spawn_entity(particle);
  }
}

void Game::split_enemy(const point &pos, const float &scale, const unsigned int &split_count){ 
  int children = 2;
  std::string mesh_id = "Asteroid01";
  for(int i = 0; i < children; ++i){
    float angle = m_random_engine.random_angle();
    float curr_scale = scale / 2.0f;

    const float vel_x = cos(glm::radians(angle)), 
                vel_y = sin(glm::radians(angle)), 
                speed = 0.5f;
    point enemy_vel = {vel_x * speed, vel_y * speed};
    std::unique_ptr<Entity> enemy = std::unique_ptr<Enemy>(new Enemy(pos, enemy_vel, mesh_id, curr_scale, angle, split_count));
    m_entity_manager.spawn_entity(enemy);
  }
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

    auto health = std::unique_ptr<Entity>(
      new Entity(bar_pos, bar_vel, bar_mesh, bar_scale, bar_angle, EntityID::LIFE));
    m_entity_manager.spawn_entity(health);
  }
}

void Game::enemy_spawner(){
  m_time_contr.enemy += m_delta_time;
  if(m_time_contr.enemy > m_conf.base_spawn_rate / m_conf.curr_diff){
    m_time_contr.enemy = 0;
    auto curr_enemy = create_enemy();
    m_entity_manager.spawn_entity(curr_enemy);
  }
}

void Game::death_cooldown(){
  m_time_contr.player += m_delta_time;
  if(m_time_contr.player > m_entity_manager.m_player.m_death_cooldown){
    m_entity_manager.m_player.m_state = PlayerState::IDLE;
    m_time_contr.player = 0;
  }
}

void Game::compute_score(const Enemy &enemy){
  unsigned int score = enemy_value(enemy);  
  bool should_increase_diff = m_score > m_conf.diff_incr_interv * m_conf.curr_step;
  
  if(should_increase_diff){
    ++m_conf.curr_step;
    m_conf.curr_diff += m_conf.diff_incr_rate;
  }

  m_score += score;

  std::cout << m_score << std::endl 
            << "curr_step: " << m_conf.curr_step << std::endl 
            << "curr diff: " << m_conf.curr_diff << std::endl;
}

unsigned int Game::enemy_value(const Enemy& enemy){
  if (enemy.m_scale < 0.3) return 25; 
  if (enemy.m_scale < 0.5) return 50; 
  return 100;
}

void Game::asteroid_player_coll(){
  if(!m_entity_manager.player_active()) return;
  std::vector<Entity*> asteroids = m_entity_manager.cache_entities(EntityID::ENEMY);
  for(auto&e : asteroids){
    if(check_coll(m_entity_manager.m_player.m_radius, m_entity_manager.m_player.m_pos, e->m_pos)){
      bool player_dead = m_entity_manager.kill_player();
      if(player_dead)
        set_state(GameState::GAMEOVER);
    }
  }
}

void Game::asteroid_proj_coll(){
  std::vector<Entity*> asteroids   = m_entity_manager.cache_entities(EntityID::ENEMY);  
  std::vector<Entity*> projectiles = m_entity_manager.cache_entities(EntityID::PROJECTILE);

  for(Entity* &ast : asteroids){
    for(Entity* &proj: projectiles){
      if(check_coll(ast->m_radius, ast->m_pos, proj->m_pos)){
        Enemy* enemy = static_cast<Enemy*>(ast);
        bool should_split = enemy->die();
        explode(enemy->m_pos, enemy->m_scale);
        compute_score(*enemy);
        if(should_split){
          split_enemy(enemy->m_pos, enemy->m_scale, enemy->m_split_count+1);
        }
        proj->destroy();
      } 
    }
  }
}

bool Game::check_coll(const float &radius_a, const point &a, const point &b) const{
  float distance = sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
  return distance < radius_a;
}

} // namespace Asteroids
