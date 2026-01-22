#pragma once
#include "entity.hpp"

namespace Asteroids {

class Player : public Entity{
public:
  Player(point pos, point vel) : Entity(pos, vel){}
  void spawn_bullet();
};

};
