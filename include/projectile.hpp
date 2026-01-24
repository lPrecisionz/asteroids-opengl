#pragma once
#include "entity.hpp"

namespace Asteroids {

class Projectile : public Entity{
public: 
  const point start_pos;
  const float m_max_distance {0.5f};

public:
  Projectile(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
    : Entity(pos, vel, mesh_id, scale, angle), start_pos(pos){}
};

} // namespace Asteroids
