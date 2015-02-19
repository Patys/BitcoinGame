#include <app.h>



void App::addBonus(float milliseconds)
{
  if(bonus_clock.getElapsedTime().asMilliseconds() > milliseconds)
    {
      std::uniform_int_distribution<int> bonus_rand(1,6);
      int rand_bonus = bonus_rand(number_generator);
      // HACK TO TESTING BONUSES
      // rand_bonus = 6;
      int time_work = 0;
      BONUS_TYPE type = B_DOUBLE_BTC;
      switch(rand_bonus)
	{
	case 1:
	  type = B_DOUBLE_BTC;
	  time_work = 2000;
	  break;
	case 2:
	  type = B_DOUBLE_ENEMIES;
	  time_work = 2000;
	  break;
	case 3:
	  type = B_EXPLODE;
	  time_work = 500;
	  break;
	case 4:
	  type = B_INVERSE_KEYS;
	  time_work = 3000;
	  break;
	case 5:
	  type = B_DARKNESS;
	  time_work = 4000;
	  break;
	case 6:
	  type = B_IMMORTALITY;
	  time_work = 5000;
	  break;
	}

      std::uniform_int_distribution<int> pos_rand(1,760);
      std::uniform_int_distribution<int> vel_rand(100,300);

      bonuses.push_back(Bonus(sf::Vector2f(pos_rand(number_generator), -150),
			      vel_rand(number_generator), type, time_work));
      bonus_clock.restart();

      std::uniform_int_distribution<int> bonus_time_rand(6000,14000);
      bonus_timer = bonus_time_rand(number_generator);
    }
}
