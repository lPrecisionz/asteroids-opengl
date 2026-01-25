#pragma once
#include <random>

namespace Asteroids{

const std::vector<float> universe_bounds {-2.0f, -1.0f, 1.0f, 2.0f};
const std::vector<float> weights {1, 0, 1};

class RandomEngine{
private: 
  std::mt19937 m_rng;
  std::uniform_real_distribution<float> m_coord_dist {-1.0f, 1.0f};
  std::uniform_real_distribution<float> m_angle_dist {0.0f, 360.0f};
  std::uniform_real_distribution<float> m_scale_dist {0.5f, 1.0f};
  std::piecewise_constant_distribution<float> m_multi_dist {universe_bounds.begin(), universe_bounds.end(), weights.begin()};

public:
  RandomEngine()  { 
    std::random_device rd; 
    m_rng.seed(rd()); 
  };
  float random_ndc()            { return m_coord_dist(m_rng); }
  float random_angle()          { return m_angle_dist(m_rng); }
  float random_scale()          { return m_scale_dist(m_rng); }
  float random_universe_coord() { return m_multi_dist(m_rng); } // returns coordinate outside NDC space for enemies spawn
};

} // namespace Asteroids
