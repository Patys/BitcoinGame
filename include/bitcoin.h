#pragma once

struct Bitcoin
{
  Bitcoin(sf::Vector2f _pos, float _vel, float _points):
    pos(_pos), vel(_vel), points(_points) {}
  sf::Vector2f pos;
  float vel;
  float points;
};
