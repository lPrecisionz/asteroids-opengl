#pragma once
#include "entity.hpp"

namespace Asteroids {

class Player : public Entity{
public:
  Player(const point &pos, const point &vel, const std::string &mesh_id) 
    : Entity(pos, vel, mesh_id){}
  void spawn_bullet();
};

};
