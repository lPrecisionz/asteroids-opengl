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
private: 
  constexpr static float uni_lower_bound =-2; 
  constexpr static float uni_upper_bound = 2;
  EnemyState m_state;

public: 
  Enemy(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
  : Entity(pos, vel, mesh_id, scale, angle), 
    m_state(EnemyState::WANDERING){}
  void update(const float &dt) override;

private:
  void handle_wandering();
  void handle_in_view();
};

}// namespace Asteroids
