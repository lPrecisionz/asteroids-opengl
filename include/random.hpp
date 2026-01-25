#pragma once
#include <random>

namespace Asteroids{

class RandomEngine{
private: 
  std::mt19937 m_rng;
  std::uniform_real_distribution<float> m_coord_dist {-1.0f, 1.0f};
  std::uniform_real_distribution<float> m_angle_dist {0.0f, 360.0f};

public:
  RandomEngine() { 
    std::random_device rd; 
    m_rng.seed(rd()); 
  };
  float random_ndc()   { return m_coord_dist(m_rng); }
  float random_angle() { return m_angle_dist(m_rng); }
};

} // namespace Asteroids
