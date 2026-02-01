#pragma once
#include "entity.hpp"
#include "../models/projectile_model.hpp"

namespace Asteroids {

constexpr float PROJ_SPEED = 1.5f;
constexpr float PROJ_MAX_DIST = 1.0f;

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
  /*Projectile(const Projectile &p)
    : Entity(p.m_pos, p.m_vel, p.m_mesh_id, p.m_scale, p.m_angle), m_start_pos(p.m_pos), m_max_distance(p.m_max_distance){
    m_id = p.m_id;
    m_radius = p.m_radius;
  }*/
  void update (const float &dt) override;
};

} // namespace Asteroids
