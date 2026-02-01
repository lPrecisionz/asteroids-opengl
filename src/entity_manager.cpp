#include "../include/entity_manager.hpp"
#include "../models/player_model.hpp"
#include "../models/projectile_model.hpp"
#include "../models/asteroids.hpp"
#include <glm/glm.hpp>

namespace Asteroids{

EntityManager::EntityManager() : m_player(spawn_player()){
  init_mesh_map();
}

void EntityManager::spawn_enemy(Enemy (*enemy)()){
  m_entities.push_back(
    std::unique_ptr<Enemy>(new Enemy(enemy()))
  );
}

void EntityManager::spawn_proj(Projectile (*proj)()){
  m_entities.push_back(
    std::unique_ptr<Projectile>(
      new Projectile(proj())
    )
  ); 
}

void EntityManager::init_mesh_map(){
  m_meshes = { 
    { "Ship",       Mesh(player_mesh    , player_vertex_attr)   },
    { "Projectile", Mesh(proj_mesh      , proj_vert_attr)       }, 
    { "Asteroid01", Mesh(asteroid01_mesh, asteroid01_vertex_arr)}
  };
}

void EntityManager::update_entities(float &dt){
for(auto &e : m_entities){
    e->update(dt);
  }
}

void EntityManager::cleanup_entities(){
  for(size_t i = 0; i < m_entities.size(); ++i){
    if(m_entities.at(i)->m_should_destroy)
      m_entities.erase(m_entities.begin() + i);
  }
}

Player EntityManager::spawn_player(){
  float spin_speed {230.0f};
  point player_pos {0, 0};
  point player_vel {0, 0};
  float player_angle {0.0f};
  float player_scale {0.0f};
  std::string player_mesh {"Ship"};

  return Player(player_pos, player_vel, player_mesh, player_scale, player_angle, spin_speed); 
}

std::vector<Entity*> EntityManager::cache_entities(const EntityID &type){
  std::vector<Entity*> cached_entities; 
  for(auto& e : m_entities){
    if(e->m_id == type)
      cached_entities.push_back(e.get());
  }
  return cached_entities;
}

} //namespace Asteroids
