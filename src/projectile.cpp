#include "../include/projectile.hpp"
#include <iostream>
#include <cmath>

namespace Asteroids{

void Projectile::update(const float &dt){
  std::cout << "projectile.update()" << std::endl;
  move(dt);
  point distance_vector = m_pos - m_start_pos;
  float traveled_distance = sqrt(pow(distance_vector.x,2) + pow(distance_vector.y, 2));
  if(traveled_distance > m_max_distance){
    std::cout << "MAX DISTANCE" << std::endl;
  }
}

} // namespace Asteroids
