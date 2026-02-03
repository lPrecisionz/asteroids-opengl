#pragma once
#include "renderer.hpp"
#include "window.hpp"
#include "mesh.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "shader.hpp"
#include "random.hpp"
#include "entity_manager.hpp"
#include <map>
#include <memory>

namespace Asteroids{

struct window_data {
  unsigned int version ;
  unsigned int width   ;
  unsigned int height  ;
  const char* name;
};

struct shader_data {
  const char* vertex_path; 
  const char* fragment_path;
};

struct game_config {
  const float  base_spawn_rate  {1.0f};
  const float  base_speed_rate  {1.0f};
  const float  diff_incr_rate   {0.01f};
  unsigned int diff_incr_interv {100};
  unsigned int curr_step        {1};
  float        curr_diff        {1.0f};
};

struct TimeController {
  float enemy {0};
  float player{0};
};

enum GameState {
  MAIN_MENU, 
  GAMEPLAY, 
  GAMEOVER
};

enum KeyState {
  FREE, 
  PRESSED, 
  HELD, 
  RELEASED
};

struct key{
  KeyState state;
};

struct InputHandler {
  key left_arrow  { FREE };
  key right_arrow { FREE };
  key space_bar   { FREE };
  key escape      { FREE };

  void free_keys() {
    left_arrow.state  = FREE; 
    right_arrow.state = FREE;
    space_bar.state   = FREE;
    escape.state      = FREE;
  }
};

class Game {
private: 
  WindowManager  m_window_manager;
  EntityManager  m_entity_manager;
  Shader         m_shader;
  game_config    m_conf;
  RandomEngine   m_random_engine;
  TimeController m_time_contr;
  InputHandler   m_input_handler;

  unsigned int   m_score      {0};
  float          m_delta_time {0};

  std::map<std::string, Mesh>          m_meshes;
  std::vector<std::unique_ptr<Entity>> m_entities;

public: 
  Game(const window_data &wd, const shader_data &sd) : 
    m_window_manager(wd.version, wd.width, wd.height, wd.name),
    m_shader(sd.vertex_path, sd.fragment_path){
    set_input_callback();
  }
  void run();

private:
  void gameplay(Renderer &renderer);

  void set_input_callback();
  void handle_input(GLFWwindow* window, int key, int scancode, int action, int mods);

  Player spawn_player();
  void spawn_health_bar();
  std::unique_ptr<Entity> create_proj();
  std::unique_ptr<Entity> create_enemy();

  void explode(const point &pos, const float &scale);
  void split_enemy(const point &pos, const float &scale, const unsigned int &split_count);

  void compute_score(const Enemy &enemy); 
  unsigned int enemy_value(const Enemy& enemy);

  void asteroid_player_coll();
  void asteroid_proj_coll();
  bool check_coll(const float &radius_a, const point &a, const point &b) const;
};

} // namespace Asteroids
