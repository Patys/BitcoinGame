#include <app.h>


void App::updateEnemies(float delta_time)
{
  static float dead_timer = 0;
  static bool start_timer = false;

  for(std::size_t i = 0; i < enemies.size(); i++)
    {
      enemies[i].update(delta_time, &player);

      if(enemies[i].isCollisionWithPlayer() && !player.isImmortality())
	{
	  start_timer = true;
	  texts.getText("txt_btc_falling").hide();
	  texts.getText("txt_enemy_falling").hide();
	  texts.getText("txt_explosion").hide();
	  texts.getText("txt_inverted_keys").hide();
	  texts.getText("txt_darkness").hide();
	}
      if(enemies[i].isCollisionWithBottom())
	{
	  enemies.erase(enemies.begin() + i);
	}
    }
  if(start_timer == true)
    {
      // here animation after dead
      for(std::size_t i = 0; i < end_game_bitcoins.size(); i++)
	{
	  end_game_bitcoins[i].update(delta_time, player);

	}
      player.denyControls();
      player.shake(delta_time);
      texts.getText("t_die").show();

      dead_timer += delta_time;
      if(dead_timer > 1)
	{
	  player.allowControls();
	  texts.getText("t_die").hide();
	  state = SCORE;
	  start_timer = false;
	  dead_timer = 0;
	  score_music.play();
	  game_music.stop();
	  setRandomTip(texts.getText("tip"));

	  game_score += player.getScore();
	  for(std::size_t i = 0; i < end_game_bitcoins.size(); i++)
	    {
	      end_game_bitcoins[i].reset();
	    }
	}
    }
}


void App::addSpeedEnemy()
{
  enemies.push_back(Enemy(speed_enemy_position, sf::Vector2f(0,800)));
}

