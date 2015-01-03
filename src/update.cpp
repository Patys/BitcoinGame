#include <app.h>

#include <cmath>


void App::update()
{

  static sf::Clock frame_clock;
  static sf::Clock sin_clock;
  static float sin_amplitude = 15;
  static float sin_time = 100;

  // Process events
  sf::Event event;
  while (window.pollEvent(event))
    {
      // Close window : exit
      if (event.type == sf::Event::Closed)
	window.close();
    }
  sf::Time frame_time = frame_clock.restart();
  if(state == GAME)
    {
      
      static float temp_resume_timer = 0;
      temp_resume_timer += frame_time.asMilliseconds();
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && temp_resume_timer > 100)
	{
	  state = RESUME;
	  temp_resume_timer = 0;
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

      if(sin_clock.getElapsedTime().asMilliseconds() > sin_time)
	{
	  sin_amplitude = -sin_amplitude;
	  t_btc_falling.setRotation(0);
	  t_enemy_falling.setRotation(0);
	  t_explosion.setRotation(0);
	  t_darkness.setRotation(0);
	  t_keys.setRotation(0);
	  sin_clock.restart();
	}
      float angel_rotate = 5*sin(sin_amplitude * frame_time.asSeconds());

      t_btc_falling.rotate(angel_rotate);
      t_enemy_falling.rotate(angel_rotate);
      t_explosion.rotate(angel_rotate);
      t_darkness.rotate(angel_rotate);
      t_keys.rotate(angel_rotate);

      for(std::size_t i = 0; i < explosion_sprites.size(); i++)
	{
	  if(!explosion_sprites[i].isPlaying())
	    explosion_sprites[i].setPosition(sf::Vector2f(-100, -100));
	  explosion_sprites[i].update(frame_time);
	}

      if(!small_explosion_sprite.isPlaying())
	small_explosion_sprite.setPosition(sf::Vector2f(-100, -100));
      small_explosion_sprite.update(frame_time);

      if(!bonus_animation_sprite.isPlaying())
	bonus_animation_sprite.setPosition(sf::Vector2f(-100,-100));
      bonus_animation_sprite.update(frame_time);

      // POINTS
      std::ostringstream _score_string;
      _score_string << player.getScore();
	  
      t_score.setString( _score_string.str());
      sf::FloatRect textRect = t_score.getLocalBounds();
      t_score.setOrigin(textRect.left + textRect.width/2.0f,
			textRect.top  + textRect.height/2.0f);
      t_score.setPosition(sf::Vector2f(400,textRect.top  + textRect.height/2.0f + 10));

    }
  //MENU
  else if(state == MENU)
    {
      sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);
      sf::Vector2f b_start_size(b_start.getLocalBounds().width, b_start.getLocalBounds().height);
      sf::Vector2f b_credits_size(b_credits.getLocalBounds().width, b_credits.getLocalBounds().height);
      sf::Vector2f b_exit_size(b_exit.getLocalBounds().width, b_exit.getLocalBounds().height);

      // Click on start menu
      bool click_on_start = isCollision(mouse_position, sf::Vector2f(1,1),
					b_start.getPosition(), b_start_size);
      
      bool click_on_credits = isCollision(mouse_position, sf::Vector2f(1,1),
					  b_credits.getPosition(), b_credits_size);
      
      bool click_on_exit = isCollision(mouse_position, sf::Vector2f(1,1),
				       b_exit.getPosition(), b_exit_size);

      static float temp_resume_timer = 0;
      temp_resume_timer += frame_time.asMilliseconds();

      if(click_on_start && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 100)
	{
	  restart();
	  temp_resume_timer = 0;
	}

      // Click on credits menu
      if(click_on_credits && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 100)
	{
	  state = CREDITS;
	  temp_resume_timer = 0;
	}

      // Click on exit menu
      if(click_on_exit && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 100)
	{
	  window.close();
	  temp_resume_timer = 0;
	}
    } 
  // SCORE
  else if(state == SCORE)
    {
      b_back.setPosition(sf::Vector2f(500,500));
      t_score.setPosition(sf::Vector2f(100,150));

      sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);
      sf::Vector2f b_back_size(b_back.getLocalBounds().width, b_back.getLocalBounds().height);
      
      bool click_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				       b_back.getPosition(), b_back_size);

      if(click_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left))
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
      sf::Vector2f b_back_size(b_back.getLocalBounds().width, b_back.getLocalBounds().height);
      
      bool click_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				       b_back.getPosition(), b_back_size);

      if(click_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left))
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
      sf::Vector2f b_menu_size(b_menu.getLocalBounds().width, b_menu.getLocalBounds().height);
      sf::Vector2f b_resume_size(b_resume.getLocalBounds().width, b_resume.getLocalBounds().height);

      bool mouse_on_menu = isCollision(mouse_position, sf::Vector2f(1,1),
				       b_menu.getPosition(), b_menu_size);

      bool mouse_on_resume = isCollision(mouse_position, sf::Vector2f(1,1),
					 b_resume.getPosition(), b_resume_size);

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
					       bonuses[i].pos, sf::Vector2f(32, 32));

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
	      bonus_animation_sprite.setPosition(bonuses[i].pos.x - 12, bonuses[i].pos.y - 12);
	      bonus_animation_sprite.play(bonus_animation);
	    }
	  bonuses.erase(bonuses.begin() + i);
	}
    }
}

void App::updateActiveBonuses()
{
  for(std::size_t i = 0; i < active_bonuses.size(); i++)
    {
      // HACK hardcoded update darkness bonus
      if(active_bonuses[i].type == B_DARKNESS && show_t_darkness)
	{
	  s_light.setPosition(sf::Vector2f(player.getPosition().x + 32 - 310,
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
	      bitcoin_timer = 150;
	      show_t_btc_falling = true;
	      alarm_sound.play();
	      break;
	    case B_DOUBLE_ENEMIES:
	      enemy_timer = 150;
	      show_t_enemy_falling = true;
	      alarm_sound.play();
	      break;
	    case B_EXPLODE:
	      {
		// deleting enemies and adding bitcoins
		show_t_explosion = true;
		std::size_t num_enemies = enemies.size();
		for(std::size_t i = 0; i < num_enemies; i++)
		  {
		    sf::Vector2f pos = enemies[i].getPosition();
		    sf::Vector2f vel = enemies[i].getVelocity();
		    float points = rand() % 20 + 1;
		    Bitcoin btc(pos, vel, points);
		    bitcoins.push_back(btc);
		  }
		enemies.clear();
	      }
	      break;
	    case B_INVERSE_KEYS:
	      player.inverseKeys();
	      show_t_keys = true;
	      break;
	    case B_DARKNESS:
	      show_t_darkness = true;
	      break;
	    }
	  active_bonuses[i].activated = true;
	}

      if(active_bonuses[i].clock.getElapsedTime().asMilliseconds() > active_bonuses[i].time_working)
	{
	  switch(active_bonuses[i].type)
	    {
	    case B_DOUBLE_BTC:
	      bitcoin_timer = 1000;
	      show_t_btc_falling = false;
	      break;
	    case B_DOUBLE_ENEMIES:
	      enemy_timer = 1000;
	      show_t_enemy_falling = false;
	      break;
	    case B_EXPLODE:
	      show_t_explosion = false;
	      break;
	    case B_INVERSE_KEYS:
	      player.inverseKeys();
	      show_t_keys = false;
	      break;
	    case B_DARKNESS:
	      show_t_darkness = false;
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
  state = GAME;
  menu_music.stop();
  score_music.stop();
  game_music.play();
}

void App::addBitcoin(float milliseconds)
{
  if(bitcoin_clock.getElapsedTime().asMilliseconds() > milliseconds)
    {
      bitcoins.push_back(Bitcoin(sf::Vector2f(rand()%760+1, -32), sf::Vector2f(0,rand()%400+50), rand()%5+1));
      bitcoin_clock.restart();
    }
}

void App::addEnemy(float milliseconds)
{
  if(enemy_clock.getElapsedTime().asMilliseconds() > milliseconds)
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
      bonuses.push_back(Bonus(sf::Vector2f(rand()%760+1, -32), rand()%500+100, type, time_work));
      bonus_clock.restart();
    }
}
