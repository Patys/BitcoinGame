#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
 public:
 GameObject() : pos(sf::Vector2f(0,0)), vel(sf::Vector2f(0,0)), collidable(false) { }
 GameObject(sf::Vector2f _pos, bool _collidable): 
  pos(_pos), vel(sf::Vector2f(0,0)), collidable(_collidable) {}
  
  const sf::Vector2f getPosition() { return pos; }
  void setPosition(sf::Vector2f _pos) { pos = _pos; }

  const sf::Vector2f getVelocity() { return vel; }
  void setVelocity(sf::Vector2f _vel) { vel = _vel; }

  const bool isCollidable() { return collidable; }
  void setCollidable(bool is_collidable) { collidable = is_collidable; }


  virtual void update(float delta_time) { pos += vel * delta_time; }
  

 protected:
  sf::Vector2f pos;
  sf::Vector2f vel;
  bool collidable;
};
