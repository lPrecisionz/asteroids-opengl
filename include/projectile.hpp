#pragma once
#include "entity.hpp"
#include "../models/projectile_model.hpp"

namespace Asteroids {

class Projectile : public Entity{
public: 
  const point m_start_pos;
  const float m_max_distance;

public:
  Projectile(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle, const EntityID &id, const float &max_distance) 
    : Entity(pos, vel, mesh_id, scale, angle), m_start_pos(pos), m_max_distance(max_distance){
    m_id = id;
    m_radius = PROJ_MESH_HEIGHT * m_scale;
  }
  void update (const float &dt) override;
};

} // namespace Asteroids
