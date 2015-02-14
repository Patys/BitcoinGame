#pragma once

#include <GameObject.h>
#include <Collision.h>
#include <player.h>

class Enemy : public GameObject
{
 public:
  Enemy(sf::Vector2f _pos, sf::Vector2f _vel):
        collision_with_player(false),
        collision_with_bottom(false)
  {
    pos = _pos;
    vel = _vel;
  }

  const bool isCollisionWithPlayer() { return collision_with_player; }
  const bool isCollisionWithBottom() { return collision_with_bottom; }

  void update(float delta_time, Player *player);

 private:
  bool collision_with_player;
  bool collision_with_bottom;
};
