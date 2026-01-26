#include "../include/player.hpp"

namespace Asteroids{

void Player::rotate(const float &angle){
  m_angle+=angle;
};

void Player::handle(){
  switch(m_state){
    case PlayerState::SPIN_RIGHT:
      rotate(m_speed);
      break;
    case PlayerState::SPIN_LEFT:
      rotate(-m_speed);
      break;
    default:
      return;
  }
}

} // namespace Asteroids
