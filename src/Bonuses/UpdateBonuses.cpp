#include <app.h>


void App::updateBonuses(float delta_time)
{
  for(std::size_t i = 0; i < bonuses.size(); i++)
    {
      bonuses[i].pos.y += bonuses[i].vel * delta_time;

      bool collision_with_player = isCollision(player.getPosition(), sf::Vector2f(96, 64),
					       sf::Vector2f(bonuses[i].pos.x, bonuses[i].pos.y+76),
					       sf::Vector2f(64, 64));

      if(bonuses[i].pos.y > 600 || collision_with_player)
	{
	  if(collision_with_player)
	    {
	      active_bonuses.push_back(ActiveBonus(bonuses[i].type, bonuses[i].time_working));

	      if(bonuses[i].type == B_EXPLODE)
		{
		  for(std::size_t i = 0; i < explosion_sprites.size(); i++)
		    {
		      std::uniform_int_distribution<int> posx_rand(1,800);
		      std::uniform_int_distribution<int> posy_rand(1,600);
		      sf::Vector2f pos = sf::Vector2f(posx_rand(number_generator),
						      posy_rand(number_generator));
		      explosion_sprites[i].setPosition(pos);
		      explosion_sprites[i].play(explosion);
		    }
		  explosion_sound.play();
		}
	    }
	  GameObject baloon;
	  baloon.setPosition(bonuses[i].pos);
	  baloons.push_back(baloon);
	  bonuses.erase(bonuses.begin() + i);
	}
    }

  // updating baloons from bonuses
  for(std::size_t i = 0; i < baloons.size(); i++)
    {
      sf::Vector2f vel(0, -300 * delta_time);
      baloons[i].setPosition(baloons[i].getPosition() + vel);
      if(baloons[i].getPosition().y < -500)
	{
	  baloons.erase(baloons.begin() + i);
	}
    }
}

void App::updateActiveBonuses()
{
  for(std::size_t i = 0; i < active_bonuses.size(); i++)
    {
      // HACK hardcoded update darkness bonus
      if(active_bonuses[i].type == B_DARKNESS)
	{
	  s_light.setPosition(sf::Vector2f(player.getPosition().x + 48 - 400,
					   player.getPosition().y + 32 - 400));
	  tex_lighting.clear( sf::Color( 0, 0, 0, 0 ) );
	  tex_lighting.draw( s_light, sf::BlendAdd ); // light - sprite, figura, cokolwiek sf::Drawable
	  tex_lighting.display(); // wywołanie tekstury, zapieczętowanie

	  s_lighting.setTexture( tex_lighting.getTexture() );
	}

      if(active_bonuses[i].activated == false)
	{
	  switch(active_bonuses[i].type)
	    {
	    case B_DOUBLE_BTC:
	      for(std::size_t i = 0; i < 10; i++)
		{
		  std::uniform_int_distribution<int> pos_rand(1,760);
		  std::uniform_int_distribution<int> vel_rand(50,400);
		  bitcoins.push_back(Bitcoin(sf::Vector2f(pos_rand(number_generator), -32),
					     sf::Vector2f(0,vel_rand(number_generator)), 1));
		}
	      texts.getText("txt_btc_falling").show();
	      alarm_sound.play();
	      break;
	    case B_DOUBLE_ENEMIES:
	      for(std::size_t i = 0; i < 5; i++)
		{
		  std::uniform_int_distribution<int> pos_rand(1,760);
		  std::uniform_int_distribution<int> vel_rand(50,400);
		  enemies.push_back(Enemy(sf::Vector2f(pos_rand(number_generator), -32),
					  sf::Vector2f(0,vel_rand(number_generator))));
		}
	      texts.getText("txt_enemy_falling").show();
	      alarm_sound.play();
	      break;
	    case B_EXPLODE:
	      {
		// deleting enemies and adding bitcoins
		texts.getText("txt_explosion").show();
		std::size_t num_enemies = enemies.size();
		for(std::size_t i = 0; i < num_enemies; i++)
		  {
		    sf::Vector2f pos = enemies[i].getPosition();
		    sf::Vector2f vel = enemies[i].getVelocity();
		    float points = 1;
		    Bitcoin btc(pos, vel, points);
		    bitcoins.push_back(btc);
		  }
		enemies.clear();
	      }
	      break;
	    case B_INVERSE_KEYS:
	      player.inverseKeys();
	      texts.getText("txt_inverted_keys").show();
	      break;
	    case B_DARKNESS:
	      texts.getText("txt_darkness").show();
	      break;
	    case B_IMMORTALITY:
	      player.setImmortality(true);
	      break;
	    }
	  active_bonuses[i].activated = true;
	}

      if(active_bonuses[i].clock.getElapsedTime().asMilliseconds() > active_bonuses[i].time_working)
	{
	  switch(active_bonuses[i].type)
	    {
	    case B_DOUBLE_BTC:
	      texts.getText("txt_btc_falling").hide();
	      break;
	    case B_DOUBLE_ENEMIES:
	      texts.getText("txt_enemy_falling").hide();
	      break;
	    case B_EXPLODE:
	      texts.getText("txt_explosion").hide();
	      break;
	    case B_INVERSE_KEYS:
	      player.inverseKeys();
	      texts.getText("txt_inverted_keys").hide();
	      break;
	    case B_DARKNESS:
	      texts.getText("txt_darkness").hide();
	      break;
	    case B_IMMORTALITY:
	      player.setImmortality(false);
	      break;
	    default:
	      break;
	    }
	  active_bonuses.erase(active_bonuses.begin() + i);
	}
    }
}


bool App::immortalityIsEnding()
{
  for(std::size_t i = 0; i < active_bonuses.size(); i++)
    {
      if(active_bonuses[i].type == B_IMMORTALITY)
	{
	  if(active_bonuses[i].clock.getElapsedTime().asMilliseconds() > 3500 &&
	     active_bonuses[i].clock.getElapsedTime().asMilliseconds() < 4000 ||
	     active_bonuses[i].clock.getElapsedTime().asMilliseconds() > 4400 &&
	     active_bonuses[i].clock.getElapsedTime().asMilliseconds() < 4700)
	    {
	      return true;
	    }
	  else return false;
	}
    }
}
