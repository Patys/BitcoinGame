#pragma once

#include <SFML/Graphics.hpp>

enum BONUS_TYPE { B_DOUBLE_BTC, B_DOUBLE_ENEMIES, B_EXPLODE, B_INVERSE_KEYS, B_DARKNESS };

class Bonus
{
 public:
 
 Bonus(sf::Vector2f _pos, float _vel, BONUS_TYPE _type, float _time_working = 0 ):
  pos(_pos), vel(_vel), type(_type), time_working(_time_working) 
  {
  }
 
  sf::Vector2f pos;
  float vel;
  BONUS_TYPE type;

  float time_working;
};

class ActiveBonus
{
 public:
 ActiveBonus(BONUS_TYPE _type, float _time_working):
  type(_type), time_working(_time_working)
  {
    clock.restart();
    activated = false;
  }
  
  bool activated;
  BONUS_TYPE type;
  float time_working;
  sf::Clock clock;
};
