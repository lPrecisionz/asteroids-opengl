#pragma once
#include "entity.hpp"
#include "../models/player_model.hpp"

namespace Asteroids {

enum PlayerState{
  SPIN_RIGHT,
  SPIN_LEFT,
  IDLE, 
  INACTIVE
};

constexpr float PLAYER_OFFSET_ANGLE = 90.0f;

class Player : public Entity{
public:
  PlayerState  m_state          { INACTIVE };
  unsigned int m_life_count     { 3 };
  float        m_spin_speed     {3.0f};
  float        m_death_cooldown {3.0f};

  Player(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle, const float &spin_speed) 
    : Entity(pos, vel, mesh_id, scale, angle, EntityID::PLAYER), m_spin_speed(spin_speed){
      m_radius = SHIP_HEIGHT*scale;
  }
  void set_state(const PlayerState s){ m_state = s;}
  void handle(const float &delta_time);
  bool is_dead() const{ return m_state == PlayerState::INACTIVE;}

private:
  void rotate(const float &angle, const float &delta_time);
};

};
