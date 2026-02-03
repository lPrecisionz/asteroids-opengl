#pragma once
#include <string>

namespace Asteroids{

struct point {
  float x, y;
  point& operator+=(const point &other){ 
    x += other.x; 
    y += other.y; 
    return *this;
  }
  point operator*(const float &factor){
    float new_x = x * factor;
    float new_y = y * factor;
    return point{new_x, new_y};
  }
  point operator-(const point &other){
    float new_x = this->x - other.x; 
    float new_y = this->y - other.y;
    return point(new_x, new_y);
  }
};

enum EntityID {
  PLAYER, 
  LIFE,
  PROJECTILE, 
  PARTICLE, 
  ENEMY
};

class Entity {
public:
  EntityID m_id;
  point m_pos;
  point m_vel;
  float m_scale {1.0f};
  float m_angle;
  float m_speed {10.0f};
  float m_radius;
  bool m_should_destroy {false};
  std::string m_mesh_id;

public:
  Entity(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle, EntityID id) 
    : m_pos(pos), m_vel(vel), m_mesh_id(mesh_id), m_scale(scale), m_angle(angle), m_id(id){}
  virtual void update(const float &dt) {}
  void destroy() { m_should_destroy = true; }
  void move(const float &dt) { m_pos += m_vel * dt; }
};

} //namespace Asteroids
