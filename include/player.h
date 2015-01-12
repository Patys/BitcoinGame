#pragma once

#include <SFML/Graphics.hpp>

class Player
{
 public:
 Player(): pos(sf::Vector2f(0,0)), score(0), inverse_keys(false), direction(0) { }
 Player(sf::Vector2f _pos): pos(_pos), score(0), inverse_keys(false), direction(0) {}

  const sf::Vector2f getPosition() const { return this->pos; }
  void setPosition(sf::Vector2f pos) { this->pos = pos; }

  void inverseKeys() { inverse_keys = !inverse_keys; }

  const float getScore() const { return score; }
  void setScore(float score) { this->score = score; }

  const int getDirection() const { return this->direction; }
  void setDirection(int direction) { this->direction = direction; } 

  void update(float delta_time);

 private:
  sf::Vector2f pos;
  float score;
  bool inverse_keys;
  int direction; // 0-left, 1-right
};
