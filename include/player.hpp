#pragma once
#include "entity.hpp"

namespace Asteroids {

class Player : public Entity{
public:
  Player(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
    : Entity(pos, vel, mesh_id, scale, angle){}
  void spawn_bullet();
};

};
