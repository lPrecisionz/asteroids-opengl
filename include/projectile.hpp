#pragma once
#include "entity.hpp"

namespace Asteroids {

class Projectile : public Entity{
public: 
  float m_lifetime {1000.0f};

public:
Projectile(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
    : Entity(pos, vel, mesh_id, scale, angle){}
};

} // namespace Asteroids
