#include "../include/projectile.hpp"
#include <cmath>

namespace Asteroids{

void Projectile::update(const float &dt){
  point distance_vector = m_pos - m_start_pos;
  float traveled_distance = sqrt(pow(distance_vector.x,2) + pow(distance_vector.y, 2));
  move(dt);
}

} // namespace Asteroids
