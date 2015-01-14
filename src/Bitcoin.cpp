#include <bitcoin.h>

#include <iostream>

std::default_random_engine generator;

void Bitcoin::update(float delta_time, Player *player)
{
  pos.x += vel.x * delta_time;
  pos.y += vel.y * delta_time;
  
  collision_with_player = isCollision(player->getPosition(), sf::Vector2f(96,64),
				      pos, sf::Vector2f(32,32));

  if(collision_with_player)
    {
      player->setScore(player->getScore() + getPoints());
    }
  if(pos.y > 600)
    collision_with_bottom = true;
  else 
    collision_with_bottom = false;
}

EndGameBitcoin::EndGameBitcoin(): 
  start_pos(0,0)
{ 
  this->reset();
}

void EndGameBitcoin::update(float delta_time, Player& player)
{
  start_pos.x += vel * side * delta_time;
  float func_y = a_func*(start_pos.x*start_pos.x) + b_func*start_pos.x - 30;

  this->position = player.getPosition() + sf::Vector2f(start_pos.x+48,func_y);
  this->setPosition(this->position);
}

void EndGameBitcoin::reset()
{  
  std::uniform_int_distribution<int> side_rand(-100,100); 
  if(side_rand(generator) < 0)
    side = -1; 
  else 
    side = 1;

  std::uniform_real_distribution<float>b_rand(5,15); 
  b_func = b_rand(generator);

  std::uniform_real_distribution<float>a_rand(1,5); 
  a_func = a_rand(generator) / 7;

  std::uniform_real_distribution<float>vel_rand(10,50);
  this->vel = vel_rand(generator);

  this->start_pos = sf::Vector2f(0,0);
  this->position = sf::Vector2f(-100,-100);
  this->setPosition(this->position);
}
