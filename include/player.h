#pragma once

#include <SFML/Graphics.hpp>

#include <random>

class Player
{
 public:
 Player(): 
  pos(sf::Vector2f(0,0)), score(0), inverse_keys(false), direction(0), control(true), immortality(false) 
    { }
 Player(sf::Vector2f _pos):
  pos(_pos), score(0), inverse_keys(false), direction(0), control(true), immortality(false)
    { }

  const sf::Vector2f getPosition() const { return this->pos; }
  void setPosition(sf::Vector2f pos) { this->pos = pos; }

  void inverseKeys() { inverse_keys = !inverse_keys; }
  void setInverseKeys(bool inverse) { this->inverse_keys = inverse; }

  const float getScore() const { return this->score; }
  void setScore(float score) { this->score = score; }

  const int getDirection() const { return this->direction; }
  void setDirection(int direction) { this->direction = direction; } 

  const bool isImmortality() const { return this->immortality; }
  void setImmortality(bool immortal) { this->immortality = immortal; }

  void update(float delta_time);
  
  void shake(float delta_time);

  bool isControl() { return this->control; }
  void allowControls() { this->control = true; }
  void denyControls() { this->control = false; }

 private:
  sf::Vector2f pos;
  float score;
  bool inverse_keys;
  int direction; // 0-left, 1-right
  bool control;
  bool immortality;
};
