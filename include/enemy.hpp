#pragma once
#include "entity.hpp"

namespace Asteroids{

class Enemy : Entity {
public:
  const float m_speed {1.0f};

public: 
  Enemy(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
  : Entity(pos, vel, mesh_id, scale, angle){}


};

}// namespace Asteroids
