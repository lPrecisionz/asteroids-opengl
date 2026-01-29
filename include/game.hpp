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

constexpr float PLAYER_OFFSET_ANGLE = 90.0f;
constexpr float PROJ_SPEED = 1.5f;

class Game {
private: 
  WindowManager m_window_manager;
  Shader        m_shader;
  Player        *m_player;
  float         m_delta_time {0};
  RandomEngine  m_random_engine;

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
  Projectile spawn_proj();
  Enemy      spawn_enemy();
  Enemy      spawn_enemy(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle);
  void split_enemy(const point &pos, const float &scale);
  void       spawn_health_bar();
  void update_entities();
  void cleanup_entities();
  std::vector<Entity*> cache_entities(const EntityID &type);
  void asteroid_player_coll();
  void asteroid_proj_coll();
  bool check_coll(const float &radius_a, const point &a, const point &b) const;
  static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

} // namespace Asteroids
