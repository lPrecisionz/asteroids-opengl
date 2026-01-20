#pragma once
#include "window.hpp"
#include "renderer.hpp"
#include "mesh.hpp"
#include "../models/model.hpp"
#include "../models/player.hpp"

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

class Game {
private: 
  WindowManager m_window_manager;
  Shader m_shader;
  Mesh   m_player {player_mesh, player_vertex_attr};
public: 
  Game(const window_data &wd, const shader_data &sd) : 
    m_window_manager(wd.version, wd.width, wd.height, wd.name),
    m_shader(sd.vertex_path, sd.fragment_path){}
  void run();
};


} // namespace Asteroids
