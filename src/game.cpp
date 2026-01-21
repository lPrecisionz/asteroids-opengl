#include "../include/game.hpp"
#include "../include/shader.hpp"

namespace Asteroids{

void Game::run(){
  while(!glfwWindowShouldClose(m_window_manager.get_window())){
    m_window_manager.clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    m_shader.use();
    m_player.draw();
    m_window_manager.swap_buffer();
    m_window_manager.poll_events();
  }
}

} // namespace Asteroids
