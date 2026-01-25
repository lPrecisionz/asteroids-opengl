#pragma once
#include "entity.hpp"
#include "../models/projectile_model.hpp"

namespace Asteroids {

class Projectile : public Entity{
public: 
  const point m_start_pos;
  constexpr static float m_max_distance {0.8f};

public:
  Projectile(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
    : Entity(pos, vel, mesh_id, scale, angle), m_start_pos(pos){
    m_radius = PROJ_HEIGHT * m_scale;
  }
  void update (const float &dt) override;
};

} // namespace Asteroids
