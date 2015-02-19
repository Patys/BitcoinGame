#include <app.h>

void App::updateGame()
{
  
  static float temp_resume_timer = 0;
  static float increase_difficulty_timer = 0;
  static float speed_enemy_timer = 0;

  speed_enemy_timer += frame_time.asMilliseconds();
  temp_resume_timer += frame_time.asMilliseconds();

  if(difficulty_timer < 10)
    increase_difficulty_timer += frame_time.asMilliseconds();

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && temp_resume_timer > 200)
    {
      state = RESUME;
      temp_resume_timer = 0;
      setRandomTip(texts.getText("tip"));
    }

  if(increase_difficulty_timer > 8000 && difficulty_timer < 10)
    {
      difficulty_timer += 0.1;
      increase_difficulty_timer = 0;
    }

  if(speed_enemy_timer > 10000)
    {
      if(!speed_enemy)
	{
	  std::uniform_int_distribution<int> posx_rand(1,800);
	  speed_enemy_position = sf::Vector2f( posx_rand(number_generator) , -32 );
	  alarm_sound.play();
	}
      speed_enemy = true;
      if(speed_enemy_timer > 12000)
	{
	  addSpeedEnemy();
	  speed_enemy = false;
	  speed_enemy_timer = 0;
	}
    }

  // ADDING NEW BITCOINS, STONES, BONUSES
  addBitcoin(bitcoin_timer);
  addEnemy(enemy_timer);
  addBonus(bonus_timer);

  updatePlayer(frame_time.asSeconds());
  updateBitcoins(frame_time.asSeconds());
  updateEnemies(frame_time.asSeconds());
  updateBonuses(frame_time.asSeconds());

  updateActiveBonuses();

  for(std::size_t i = 0; i < explosion_sprites.size(); i++)
    {
      if(!explosion_sprites[i].isPlaying())
	explosion_sprites[i].setPosition(sf::Vector2f(-100, -100));
      explosion_sprites[i].update(frame_time);
    }

  if(!small_explosion_sprite.isPlaying())
    small_explosion_sprite.setPosition(sf::Vector2f(-100, -100));
  small_explosion_sprite.update(frame_time);

  // POINTS
  std::ostringstream _score_string;
  _score_string << player.getScore();
  texts.getText("score").text().setOrigin(texts.getText("score").getCenterOfText());
  texts.getText("score").text().setPosition(sf::Vector2f(400,30));
  texts.getText("score").text().setString( _score_string.str());

}
