#include "../include/game.hpp"

constexpr unsigned int OGL_VER = 3;
constexpr unsigned int WINDOW_WIDTH   = 800; 
constexpr unsigned int WINDOW_HEIGHT  = 800; 
const char* WINDOW_NAME = "Asteroids";

Asteroids::window_data win_data(OGL_VER, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);

int main(){
  Asteroids::Game game {win_data};
  game.run();

  return 0;
}
