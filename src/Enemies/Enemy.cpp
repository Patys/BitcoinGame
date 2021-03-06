#include <enemy.h>

void Enemy::update(float delta_time, Player *player)
{
  pos.x += vel.x * delta_time;
  pos.y += vel.y * delta_time;

  collision_with_player = isCollision(player->getPosition(), sf::Vector2f(96,64),
				      pos, sf::Vector2f(32,32));

  if(pos.y > 600)
    collision_with_bottom = true;
  else 
    collision_with_bottom = false;
}
