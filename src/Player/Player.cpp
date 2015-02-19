#include <player.h>

std::default_random_engine player_rand_generator;

void Player::update(float delta_time)
{
  this->direction = 0;

  if(this->control)
    {

      if(inverse_keys == false)
	{
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
	     sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	    {
	      pos.y -= 500 * delta_time;
	      this->direction = 3;
	    }
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
	     sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	    {
	      pos.y += 500 * delta_time;
	      this->direction = 4;
	    }
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
	     sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	    {
	      pos.x -= 500 * delta_time;
	      this->direction = 1;
	    }
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
	     sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	    {
	      pos.x += 500 * delta_time;
	      this->direction = 2;
	    }
	}
      else
	{
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
	     sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	    {
	      pos.y += 500 * delta_time;
	      this->direction = 4;
	    }
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
	     sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	    {
	      pos.y -= 500 * delta_time;
	      this->direction = 3;
	    }
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
	     sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	    {
	      pos.x += 500 * delta_time;
	      this->direction = 2;
	    }
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
	     sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	    {
	      pos.x -= 500 * delta_time;
	      this->direction = 1;
	    }
	}
    }

  if(pos.y > 600 - 64)
    pos.y = 600 - 64;
  if(pos.y < 0)
    pos.y = 0;
  if(pos.x > 800 - 96)
    pos.x = 800 - 96;
  if(pos.x < 0)
    pos.x = 0;
}

void Player::shake(float delta_time)
{
  std::uniform_real_distribution<float>rand_vel(-300,300); 
  pos.x += rand_vel(player_rand_generator) * delta_time;
  pos.y += rand_vel(player_rand_generator) * delta_time;
}
