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
constexpr float SPIN_SPEED = 250.0f;
constexpr float PROJ_SPEED = 0.05f;

class Game {
private: 
  WindowManager m_window_manager;
  Shader m_shader;
  Player *m_player;
  std::map<std::string, Mesh> m_meshes;
  std::vector<std::unique_ptr<Entity>> m_entities;
  RandomEngine m_random_engine;

public: 
  Game(const window_data &wd, const shader_data &sd) : 
    m_window_manager(wd.version, wd.width, wd.height, wd.name),
    m_shader(sd.vertex_path, sd.fragment_path){
    init_mesh_map();
  }
  void run();

private:
  void handle_input(const float &dt);
  void init_mesh_map();
  Player     spawn_player();
  Projectile spawn_proj();
  Enemy      spawn_enemy();
  void       spawn_health_bar();
  void update_entities(const float &dt);
  void cleanup_entities();
};

} // namespace Asteroids
