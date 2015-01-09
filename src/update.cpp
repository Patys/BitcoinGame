#include <app.h>

#include <cmath>


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
    }
  sf::Time frame_time = frame_clock.restart();

  texts.update(frame_time.asSeconds());


  if(state == GAME)
    {
      
      static float temp_resume_timer = 0;
      static float increase_difficulty_timer = 0;

      temp_resume_timer += frame_time.asMilliseconds();
      
      if(difficulty_timer < 4)
	increase_difficulty_timer += frame_time.asMilliseconds();

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && temp_resume_timer > 100)
	{
	  state = RESUME;
	  temp_resume_timer = 0;
	}
      
      if(increase_difficulty_timer > 2000 && difficulty_timer < 4)
	{
	  difficulty_timer += 0.1;
	  increase_difficulty_timer = 0;
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

      if(mouse_on_start && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 100)
	{
	  restart();
	  temp_resume_timer = 0;
	}

      // Click on credits menu
      if(mouse_on_credits && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 100)
	{
	  state = CREDITS;
	  temp_resume_timer = 0;
	}

      // Click on exit menu
      if(mouse_on_exit && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 100)
	{
	  window.close();
	  temp_resume_timer = 0;
	}
    } 
  // SCORE
  else if(state == SCORE)
    {
      texts.getText("score").text().setPosition(sf::Vector2f(100,150));

      sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);

      bool mouse_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_back").text().getPosition(),
				       texts.getText("btn_back").getSizeOfText());

      if(mouse_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  state = MENU;
	  score_music.stop();
	  menu_music.play();
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

      if(mouse_on_menu && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 100)
	{
	  state = MENU;
	  game_music.stop();
	  menu_music.play();
	  temp_resume_timer = 0;
	}
      if(mouse_on_resume && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 100)
	{
	  state = GAME;
	  temp_resume_timer = 0;
	}
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && temp_resume_timer > 100)
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
  for(std::size_t i = 0; i < enemies.size(); i++)
    {
      enemies[i].update(delta_time, &player);

      if(enemies[i].isCollisionWithPlayer())
	{
	  state = SCORE;
	  score_music.play();
	  game_music.stop();
	}

      if(enemies[i].isCollisionWithBottom())
	{
	  enemies.erase(enemies.begin() + i);
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
		      sf::Vector2f pos = sf::Vector2f(rand()%800, rand()%600);
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
	  s_light.setPosition(sf::Vector2f(player.getPosition().x + 48 - 310,
					   player.getPosition().y + 32 - 310));
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
		  bitcoins.push_back(Bitcoin(sf::Vector2f(rand()%760+1, -32),
					     sf::Vector2f(0,rand()%400+50),
					     1));
		}
	      texts.getText("txt_btc_falling").show();
	      alarm_sound.play();
	      break;
	    case B_DOUBLE_ENEMIES:
	      for(std::size_t i = 0; i < 5; i++)
		{
		  enemies.push_back(Enemy(sf::Vector2f(rand()%760+1, -32), sf::Vector2f(0,rand()%400+50)));
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

  player.setPosition(sf::Vector2f(300,400));
  player.setScore(0);

  difficulty_timer = 1;

  state = GAME;

  menu_music.stop();
  score_music.stop();
  game_music.play();

  /* HACK: TEMPORARY OFF
  texts.getText("txt_btc_falling").hide();
  texts.getText("txt_enemy_falling").hide();
  texts.getText("txt_explosion").hide();
  texts.getText("txt_inverted_keys").hide();
  texts.getText("txt_darkness").hide();
  */
}

void App::addBitcoin(float milliseconds)
{
  if(bitcoin_clock.getElapsedTime().asMilliseconds() > milliseconds)
    {
      bitcoins.push_back(Bitcoin(sf::Vector2f(rand()%760+1, -32), sf::Vector2f(0,rand()%400+50), 1));
      bitcoin_clock.restart();
    }
}

void App::addEnemy(float milliseconds)
{
  if(enemy_clock.getElapsedTime().asMilliseconds() * difficulty_timer > milliseconds)
    {
      enemies.push_back(Enemy(sf::Vector2f(rand()%760+1, -32), sf::Vector2f(0,rand()%400+50)));
      enemy_clock.restart();
    }
}


void App::addBonus(float milliseconds)
{
  if(bonus_clock.getElapsedTime().asMilliseconds() > milliseconds)
    {
      int rand_bonus = rand()%5+1;
      // HACK TO TESTING BONUSES
      // rand_bonus = 5;
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
	}
      bonuses.push_back(Bonus(sf::Vector2f(rand()%760+1, -150), rand()%300+100, type, time_work));
      bonus_clock.restart();
    }
}
