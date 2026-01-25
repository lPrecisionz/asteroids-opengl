#pragma once
#include <random>

namespace Asteroids{

class RandomEngine{
private: 
  std::mt19937 m_device;

public:
  RandomEngine(const int& seed) {m_device.seed(seed);};
};

} // namespace Asteroids
