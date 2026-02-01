#pragma once
#include "entity.hpp"
#include "../models/player_model.hpp"

namespace Asteroids {

enum PlayerState{
  SPIN_RIGHT,
  SPIN_LEFT,
  IDLE, 
  DEAD
};

class Player : public Entity{
public:
  PlayerState m_state { IDLE };
  float m_spin_speed;
  Player(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle, const float &spin_speed) 
    : Entity(pos, vel, mesh_id, scale, angle), m_spin_speed(spin_speed){
      m_id     = EntityID::PLAYER;
      m_radius = SHIP_HEIGHT*scale;
  }
  void set_state(const PlayerState s){ m_state = s;}
  void handle(const float &delta_time);
  bool is_dead() const{ return m_state == PlayerState::DEAD;}

private:
  void rotate(const float &angle, const float &delta_time);
};

};
