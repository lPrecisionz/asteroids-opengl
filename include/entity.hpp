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
};

class Entity {
public:
  point m_pos;
  point m_vel;
  float m_scale {1.0f};
  float m_angle;
  std::string m_mesh_id;

public:
  Entity(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
    : m_pos(pos), m_vel(vel), m_mesh_id(mesh_id), m_scale(scale), m_angle(angle){}
  void move() { m_pos += m_vel;}
};

} //namespace Asteroids
