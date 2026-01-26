#pragma once
#include "entity.hpp"
#include "../models/player_model.hpp"

namespace Asteroids {

enum PlayerState{
  SPIN_RIGHT,
  SPIN_LEFT,
  IDLE
};

class Player : public Entity{
public:
  PlayerState m_state { IDLE };
  Player(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
    : Entity(pos, vel, mesh_id, scale, angle){
      m_id     = EntityID::PLAYER;
      m_radius = SHIP_HEIGHT*scale;
  }
  void rotate(const float &angle);
  void handle();
};

};
