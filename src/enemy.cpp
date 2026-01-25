#include "../include/enemy.hpp"

namespace Asteroids{

void Enemy::update(const float &dt){
  move(dt);
  if(m_state == OutOfBounds){

  }
}

} // namespace Asteroids
