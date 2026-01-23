#include "../include/player.hpp"

namespace Asteroids{

void Player::rotate(const float &angle){
  m_angle+=angle;
};

} // namespace Asteroids
