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
  point& operator*(const float &factor){
    x *= factor; 
    y *= factor; 
    return *this;
  }
  point operator-(const point &other){
    float new_x = this->x - other.x; 
    float new_y = this->y - other.y;
    return point(new_x, new_y);
  }
};

class Entity {
public:
  point m_pos;
  point m_vel;
  float m_scale {1.0f};
  float m_angle;
  float m_speed {10.0f};
  bool m_should_destroy {false};
  std::string m_mesh_id;

public:
  Entity(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle) 
    : m_pos(pos), m_vel(vel), m_mesh_id(mesh_id), m_scale(scale), m_angle(angle){}
  void move(const float &dt) { m_pos += m_vel ; }
  virtual void update(const float &dt) {}
};

} //namespace Asteroids
