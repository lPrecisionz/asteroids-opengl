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
  void spawn_entity(std::unique_ptr<Entity> &entity);
  void update_entities(float &dt);
  void cleanup_entities();
  std::vector<Entity*> cache_entities(const EntityID &type);

private: 
  void    init_mesh_map();
  Player  spawn_player();
};

} //namespace Asteroids
