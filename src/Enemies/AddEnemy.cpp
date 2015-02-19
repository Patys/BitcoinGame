#include <app.h>


void App::addEnemy(float milliseconds)
{
  if(enemy_clock.getElapsedTime().asMilliseconds() * difficulty_timer > milliseconds)
    {
      std::uniform_int_distribution<int> pos_rand(1,760);
      std::uniform_int_distribution<int> vel_rand(50,400);
      enemies.push_back(Enemy(sf::Vector2f(pos_rand(number_generator), -32),
			      sf::Vector2f(0,vel_rand(number_generator))));
      enemy_clock.restart();
    }
}
