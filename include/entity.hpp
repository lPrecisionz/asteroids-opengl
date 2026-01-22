#pragma once

namespace Asteroids{

struct point {
  float x, y;
  point& operator+=(point &other){ 
    x += other.x; 
    y += other.y; 
    return *this;
  }
};

class Entity {
public:
  point m_pos;
  point m_vel;

public:
  Entity(const point &pos, const point &vel) : m_pos(pos), m_vel(vel){}
  void move() {m_pos += m_vel;}
};

} //namespace Asteroids
