#pragma once
#include "window.hpp"
#include "renderer.hpp"

namespace Asteroids{

struct window_data {
  unsigned int version ;
  unsigned int width   ;
  unsigned int height  ;
  const char* name;
};

class Game {
private: 
  WindowManager m_window_manager;

public: 
  Game(window_data wd) : m_window_manager(wd.version, wd.width, wd.height, wd.name){}
  void run();
};

};
