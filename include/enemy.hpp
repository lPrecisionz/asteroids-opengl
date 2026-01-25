#pragma once
#include "entity.hpp"

namespace Asteroids{

enum EnemyState {
  ALIVE, 
  OUT_OF_BOUND, 
  KILLED
};

class Enemy : Entity {
public: 
  EnemyState m_state;
public: 
  Enemy(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
  : Entity(pos, vel, mesh_id, scale, angle), 
    m_state(EnemyState::ALIVE){}
};

}// namespace Asteroids
