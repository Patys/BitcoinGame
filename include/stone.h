#pragma once


struct Stone
{
  Stone(sf::Vector2f _pos, float _vel):
    pos(_pos), vel(_vel) {}
  sf::Vector2f pos;
  float vel;
};
