#pragma once

#include <GameObject.h>
#include <Collision.h>
#include <player.h>

class Bitcoin : public GameObject
{
 public:
 Bitcoin(sf::Vector2f _pos, sf::Vector2f _vel, float _points)
   {
     pos = _pos;
     vel = _vel;
     points = _points;
   }

    const float getPoints() { return points; }
    void setPoints(float _points) { points = _points; } 

    const bool isCollisionWithPlayer() { return collision_with_player; }
    const bool isCollisionWithBottom() { return collision_with_bottom; }

    void update(float delta_time, Player *player);

 private:
  float points;
  bool collision_with_player;
  bool collision_with_bottom;
};
