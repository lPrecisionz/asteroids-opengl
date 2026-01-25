#pragma once
#include "entity.hpp"

namespace Asteroids{

enum EnemyState {
  WANDERING,    // Spawned and hasn't reached viewspace
  IN_VIEW,      // Reached viewspace 
  DEAD,         // Has been killed
  OUT_OF_BOUNDS // Has left viewspace
};

class Enemy : public Entity {
public: 
  EnemyState m_state;
public: 
  Enemy(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
  : Entity(pos, vel, mesh_id, scale, angle), 
    m_state(EnemyState::WANDERING){}
  void update(const float &dt);
};

}// namespace Asteroids
