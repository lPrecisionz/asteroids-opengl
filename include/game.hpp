#pragma once
#include "window.hpp"
#include "renderer.hpp"
#include "mesh.hpp"
#include "../models/model.hpp"
#include "../models/player_model.hpp"
#include "entity.hpp"
#include "player.hpp"
#include <map>

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

struct player_data {
  point player_pos; 
  point player_vel;
  float player_angle;
  float player_scale;
  std::string player_mesh;
};

constexpr float SPIN_SPEED = 5.0f;

class Game {
private: 
  WindowManager m_window_manager;
  Shader m_shader;
  Player m_player;
  std::map<std::string, Mesh> m_meshes;
  std::vector<Entity> m_entities;

public: 
  Game(const window_data &wd, const shader_data &sd, const player_data &pd) : 
    m_window_manager(wd.version, wd.width, wd.height, wd.name),
    m_shader(sd.vertex_path, sd.fragment_path), 
    m_player(Player(pd.player_pos, pd.player_vel, pd.player_mesh, pd.player_angle, pd.player_scale)){
    init_mesh_map();
  }
  void run();


private:
  void handle_input(glm::mat4 &model);
  void init_mesh_map();
  void spawn_player();
  void spawn_health_bar();
};


} // namespace Asteroids
