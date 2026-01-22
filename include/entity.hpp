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
  void move() {m_pos += m_vel;}
};

} //namespace Asteroids
