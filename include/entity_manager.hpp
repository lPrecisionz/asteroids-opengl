#pragma once

#include "mesh.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "enemy.hpp"
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
  void spawn_enemy(Enemy (*create_enemy)(void));
  void spawn_enemy(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle, const unsigned int &split_count, Enemy (*create_enemy)(const point &pos, const point &vel, const std::string &mesh_id, const float &scale, const float &angle, const unsigned int &split_count));
  void spawn_proj(Projectile (*create_projectile)());

private: 
  void       init_mesh_map();
  void       update_entities(float &dt);
  void       cleanup_entities();
  Player     spawn_player();

  std::vector<Entity*> cache_entities(const EntityID &type);
};

} //namespace Asteroids
