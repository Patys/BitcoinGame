#pragma once

#include <random>

#include <GameObject.h>
#include <Collision.h>
#include <player.h>

class Bitcoin : public GameObject
{
 public:
 Bitcoin(sf::Vector2f _pos, sf::Vector2f _vel, float _points):
     collision_with_player(false),
     collision_with_bottom(false)
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

class EndGameBitcoin : public GameObject
{
 public:
  EndGameBitcoin();

  void update(float delta_time, Player& player);
  void reset();
  const sf::Vector2f getPosition() const { return this->position; }

 private:
  sf::Vector2f start_pos;
  sf::Vector2f position;
  int side;
  float b_func;
  float a_func;
  float vel;
};
