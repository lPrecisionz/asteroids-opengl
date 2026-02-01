#pragma once

#include "mesh.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "enemy.hpp"
#include "random.hpp"
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
  void spawn_enemy(Enemy (*enemy)());
  void spawn_proj(Projectile (*proj)());

private: 
  void       init_mesh_map();
  void       update_entities(float &dt);
  void       cleanup_entities();
  Player     spawn_player();
  Projectile create_proj();
  Enemy      create_enemy(RandomEngine &rd);
  Enemy      create_enemy(const Enemy& e);

  std::vector<Entity*> cache_entities(const EntityID &type);
};

} //namespace Asteroids
