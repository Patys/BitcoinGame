#include <app.h>

void App::addBitcoin(float milliseconds)
{
  if(bitcoin_clock.getElapsedTime().asMilliseconds() > milliseconds)
    {
      std::uniform_int_distribution<int> pos_rand(1,760);
      std::uniform_int_distribution<int> vel_rand(50,400);
      bitcoins.push_back(Bitcoin(sf::Vector2f(pos_rand(number_generator), -32),
				 sf::Vector2f(0,vel_rand(number_generator)), 1));
      bitcoin_clock.restart();
    }
}
