#include "../include/game.hpp"
#include "../include/shader.hpp"

namespace Asteroids{
void Game::run(){
  while(!glfwWindowShouldClose(m_window_manager.get_window())){
    m_shader.use();
    m_player.draw();
    glfwPollEvents();  
    glfwSwapBuffers(m_window_manager.get_window());
  }
}

} // namespace Asteroids
