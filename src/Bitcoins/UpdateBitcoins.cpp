#include <app.h>


void App::updateBitcoins(float delta_time)
{
  for(std::size_t i = 0; i < bitcoins.size(); i++)
    {
      bitcoins[i].update(delta_time, &player);

      if(bitcoins[i].isCollisionWithBottom() || bitcoins[i].isCollisionWithPlayer())
	{
	  if(bitcoins[i].isCollisionWithPlayer())
	    {
	      small_explosion_sprite.setPosition(bitcoins[i].getPosition());
	      small_explosion_sprite.play(small_explosion);
	      btc_sound.play();
	    }

	  bitcoins.erase(bitcoins.begin() + i);
	}
    }
}
