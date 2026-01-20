#include "../include/game.hpp"
#include "../include/shader.hpp"

namespace Asteroids{
void Game::run(){
  while(!glfwWindowShouldClose(m_window_manager.get_window())){
    glfwPollEvents();  
    glfwSwapBuffers(m_window_manager.get_window());
  }
}

} // namespace Asteroids
