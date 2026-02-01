#pragma once

#include "mesh.hpp"
#include "entity.hpp"
#include "player.hpp"
#include <map>
#include <vector>
#include <memory>

namespace Asteroids{

class EntityManager {
public:
  Player m_player; 
  std::map<std::string, Mesh>          m_meshes;
  std::vector<std::unique_ptr<Entity>> m_entities;

public : 
  EntityManager();

private: 
  void init_mesh_map();
  void update_entities();
  void cleanup_entities();
  void spawn_player();
  std::vector<Entity*> cache_entities(const EntityID &type);
};

} //namespace Asteroids
