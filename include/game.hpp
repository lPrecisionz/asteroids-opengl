#pragma once
#include "window.hpp"
#include "mesh.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "shader.hpp"
#include "random.hpp"
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

enum GameState {
  MAIN_MENU, 
  GAMEPLAY, 
  GAMEOVER
};

class Game {
private: 
  WindowManager m_window_manager;
  Shader        m_shader;
  Player        *m_player;
  unsigned int  m_score {0};
  float         m_delta_time {0};
  RandomEngine  m_random_engine;
  game_config   m_conf;

  std::map<std::string, Mesh>          m_meshes;
  std::vector<std::unique_ptr<Entity>> m_entities;

public: 
  Game(const window_data &wd, const shader_data &sd) : 
    m_window_manager(wd.version, wd.width, wd.height, wd.name),
    m_shader(sd.vertex_path, sd.fragment_path){
    init_mesh_map();
    set_input_callback();
  }
  void run();

private:
  void set_input_callback();
  void handle_input(GLFWwindow* window, int key, int scancode, int action, int mods);
  void init_mesh_map();
  Player     spawn_player();
  Projectile create_proj();
  Enemy      create_enemy();
  Enemy      create_enemy(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle, const unsigned int &split_count);
  void explode(const point &pos, const float &scale);
  void split_enemy(const point &pos, const float &scale, const unsigned int &split_count);
  void spawn_health_bar();
  void compute_score(const Enemy &enemy); 
  unsigned int enemy_value(const Enemy& enemy);
  void update_entities();
  void cleanup_entities();
  std::vector<Entity*> cache_entities(const EntityID &type);
  void asteroid_player_coll();
  void asteroid_proj_coll();
  bool check_coll(const float &radius_a, const point &a, const point &b) const;
};

} // namespace Asteroids
