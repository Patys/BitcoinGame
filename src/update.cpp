#include <app.h>
#include <Network.h>

#include <cmath>

std::vector<std::string> tips = {
  {"Avoid shurikens."},
  {"Take every bitcoin!"},
  {"Bonuses contain good and bad things."},
  {"Check out bitcoin.org"},
  {"Tell to friends about this game."},
  {"Go to bitcoin-patys.rhcloud.com and give me some feedback!"},
  {"Enjoy the game :D"}
};

void setRandomTip(ShakingText& text);


void App::update()
{
  static sf::Clock frame_clock;

  // Process events
  sf::Event event;
  while (window.pollEvent(event))
    {
      // Close window : exit
      if (event.type == sf::Event::Closed)
	window.close();
      if (event.type == sf::Event::LostFocus)
	{
	  if(state == GAME)
	    state = RESUME;
	}
    }

  sf::Time frame_time = frame_clock.restart();

  texts.update(frame_time.asSeconds());


  if(state == GAME)
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
  //MENU
  else if(state == MENU)
    {
      texts.getText("game_score").text().setPosition(sf::Vector2f(400,550));
      sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);
     
      // Click on start menu
      bool mouse_on_start = isCollision(mouse_position, sf::Vector2f(1,1),
					texts.getText("btn_start").text().getPosition(),
					texts.getText("btn_start").getSizeOfText());
      
      bool mouse_on_credits = isCollision(mouse_position, sf::Vector2f(1,1),
					  texts.getText("btn_credits").text().getPosition(),
					  texts.getText("btn_credits").getSizeOfText());
      
      bool mouse_on_exit = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_exit").text().getPosition(),
				       texts.getText("btn_exit").getSizeOfText());

      static float temp_resume_timer = 0;
      temp_resume_timer += frame_time.asMilliseconds();

      if(mouse_on_start && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 200)
	{
	  restart();
	  temp_resume_timer = 0;
	}

      // Click on credits menu
      if(mouse_on_credits && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 200)
	{
	  state = CREDITS;
	  temp_resume_timer = 0;
	}

      // Click on exit menu
      if(mouse_on_exit && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 200)
	{
	  window.close();
	  temp_resume_timer = 0;
	}
    } 
  // SCORE
  else if(state == SCORE)
    {
      texts.getText("score").text().setPosition(sf::Vector2f(100,150));
      texts.getText("game_score").text().setPosition(sf::Vector2f(100,200));

      sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);

      bool mouse_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_back").text().getPosition(),
				       texts.getText("btn_back").getSizeOfText());
      bool mouse_on_restart = isCollision(mouse_position, sf::Vector2f(1,1),
					  texts.getText("btn_restart").text().getPosition(),
					  texts.getText("btn_restart").getSizeOfText());

      if(mouse_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  state = MENU;
	  score_music.stop();
	  menu_music.play();
	}

      if(mouse_on_restart && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  restart();
	}

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
	  sendScore(player.getScore(), "TEST", 0);
	  state = MENU;
	}	 
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
	  state = MENU;
	  score_music.stop();
	  menu_music.play();
	}
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
	  restart();
	}
    }
  else if(state == CREDITS)
    {
      sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);
      
      bool mouse_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_back").text().getPosition(),
				       texts.getText("btn_back").getSizeOfText());

      if(mouse_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  state = MENU;
	}

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
	  state = MENU;
	}
    }
  else if(state == RESUME)
    {
      sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);
      
      bool mouse_on_menu = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_menu").text().getPosition(), 
				       texts.getText("btn_menu").getSizeOfText());

      bool mouse_on_resume = isCollision(mouse_position, sf::Vector2f(1,1),
					 texts.getText("btn_resume").text().getPosition(),
					 texts.getText("btn_resume").getSizeOfText());

      static float temp_resume_timer = 0;
      temp_resume_timer += frame_time.asMilliseconds();

      if(mouse_on_menu && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 200)
	{
	  state = MENU;
	  game_music.stop();
	  menu_music.play();
	  temp_resume_timer = 0;
	}
      if(mouse_on_resume && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 200)
	{
	  state = GAME;
	  temp_resume_timer = 0;
	}
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && temp_resume_timer > 200)
	{
	  state = GAME;
	  temp_resume_timer = 0;
	}
    }
}

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
	  std::ostringstream _score_string;
	  _score_string << game_score;
	  texts.getText("game_score").text().setString("Bitcoins: " + _score_string.str());
	  texts.getText("game_score").text().setOrigin(texts.getText("game_score").getCenterOfText());

	  for(std::size_t i = 0; i < end_game_bitcoins.size(); i++)
	    {
	      end_game_bitcoins[i].reset();
	    }
	}
    }
}

void App::updatePlayer(float delta_time)
{
  player.update(delta_time);

}

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

void App::restart()
{
  enemies.clear();
  bitcoins.clear();
  bonuses.clear();
  active_bonuses.clear();

  player.setPosition(sf::Vector2f(300,400));
  player.setScore(0);
  player.setImmortality(false);
  player.setInverseKeys(false);
  player.allowControls();

  difficulty_timer = 1;

  state = GAME;

  menu_music.stop();
  score_music.stop();
  game_music.play();

  setting_skins.addEnemySkin(ES_SHURIKEN);
  setting_skins.setEnemySkin(ES_SHURIKEN);

  checkSettings();

  texts.getText("txt_btc_falling").hide();
  texts.getText("txt_enemy_falling").hide();
  texts.getText("txt_explosion").hide();
  texts.getText("txt_inverted_keys").hide();
  texts.getText("txt_darkness").hide();
}

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


void App::addBonus(float milliseconds)
{
  if(bonus_clock.getElapsedTime().asMilliseconds() > milliseconds)
    {      
      std::uniform_int_distribution<int> bonus_rand(1,6);
      int rand_bonus = bonus_rand(number_generator);
      // HACK TO TESTING BONUSES
      // rand_bonus = 6;
      int time_work = 0;
      BONUS_TYPE type;
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

void App::addSpeedEnemy()
{
  enemies.push_back(Enemy(speed_enemy_position, sf::Vector2f(0,800)));
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

void App::checkSettings()
{

  PLAYERSKINS player_skin = setting_skins.getCurrentPlayerSkin();
  switch(player_skin)
    {
    case PS_BASIC:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet1.png"));
      break;
    case PS_FACE:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet.png"));
      break;
    }
  ENEMYSKINS enemy_skin = setting_skins.getCurrentEnemySkin();
  switch(enemy_skin)
    {
    case ES_STONE:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/stone.png"));
      break;
    case ES_SHURIKEN:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/shuriken.png"));
      break;
    }
}

void setRandomTip(ShakingText& text)
{
  std::uniform_int_distribution<int> distribution(0,tips.size()-1);
  int i = distribution(number_generator);
  text.text().setString(tips[i]);
  text.text().setOrigin(text.getCenterOfText());
}
