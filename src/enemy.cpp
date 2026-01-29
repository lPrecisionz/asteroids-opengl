#include "../include/enemy.hpp"
#include <iostream>

namespace Asteroids{

void Enemy::update(const float &dt){
  move(dt);
  switch(m_state){
    case EnemyState::WANDERING:
      handle_wandering();
      break;
    case EnemyState::IN_VIEW: 
      handle_in_view();
      break;
    case EnemyState::DEAD: 
      destroy();
      break;
    case EnemyState::OUT_OF_BOUNDS:
      destroy();
      break;
  }
}

void Enemy::handle_wandering(){
  if(m_pos.x > uni_upper_bound || m_pos.x < uni_lower_bound)
    m_vel.x *=-1;
  if(m_pos.y > uni_upper_bound || m_pos.y < uni_lower_bound)
    m_vel.y *=-1;
  if(is_in_view())
    m_state = EnemyState::IN_VIEW;
}

void Enemy::handle_in_view(){
  if(!is_in_view())
    m_state = EnemyState::OUT_OF_BOUNDS;
}

bool Enemy::is_in_view(){
  bool x_in_view = (m_pos.x + m_radius) > -1 && (m_pos.x - m_radius) < 1, 
       y_in_view = (m_pos.y + m_radius) > -1 && (m_pos.y - m_radius) < 1;
  return x_in_view && y_in_view;
}

bool Enemy::die(){
  m_state = EnemyState::DEAD;
  return m_scale > 0.1f && m_split_count < 1;
}

} // namespace Asteroids
