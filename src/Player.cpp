#include <player.h>

void Player::update(float delta_time)
{
  if(inverse_keys == false)
    {
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
	 sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	pos.y -= 500 * delta_time;
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
	 sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	pos.y += 500 * delta_time;
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
	 sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	pos.x -= 500 * delta_time;
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
	 sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	pos.x += 500 * delta_time;
    }
  else
    {
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
	 sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	pos.y += 500 * delta_time;
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
	 sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	pos.y -= 500 * delta_time;
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
	 sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	pos.x += 500 * delta_time;
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
	 sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	pos.x -= 500 * delta_time;
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
