#include "../include/player.hpp"

namespace Asteroids{

void Player::rotate(const float &angle, const float &delta_time){
  m_angle+= angle * delta_time;
};

void Player::handle(const float &delta_time){
  switch(m_state){
    case PlayerState::SPIN_RIGHT:
      rotate(-m_spin_speed, delta_time);
      break;
    case PlayerState::SPIN_LEFT:
      rotate(m_spin_speed, delta_time);
      break;
    case PlayerState::INACTIVE:
      break;
    default:
      return;
  }
}

} // namespace Asteroids
