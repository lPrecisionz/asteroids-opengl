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
  constexpr static float baseline_hitbox = 1;
  EnemyState  m_state;
  const float m_hitbox_size;

public: 
  Enemy(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle, const unsigned int &split_count) 
  : Entity(pos, vel, mesh_id, scale, angle, EntityID::ENEMY), 
    m_state       (EnemyState::WANDERING), 
    m_split_count (split_count),
    m_hitbox_size (baseline_hitbox * scale){
    m_id = EntityID::ENEMY;
    m_radius = m_hitbox_size/2.0f; 
  }
  const unsigned int m_split_count; 
  void update(const float &dt) override;
  bool die();

private:
  void handle_wandering();
  void handle_in_view();
  bool is_in_view();
};

}// namespace Asteroids
