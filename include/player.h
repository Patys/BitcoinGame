#pragma once

#include <SFML/Graphics.hpp>

class Player
{
 public:
  Player() {}
 Player(sf::Vector2f _pos): pos(_pos) { inverse_keys = false; }

  const sf::Vector2f getPosition() { return pos; }
  void setPosition(sf::Vector2f _pos) { pos = _pos; }

  void inverseKeys() { inverse_keys = !inverse_keys; }

  const float getScore() { return score; }
  void setScore(float _score) { score = _score; }

  void update(float delta_time);

 private:
  sf::Vector2f pos;
  float score;
  bool inverse_keys;
};
