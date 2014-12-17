#include <app.h>

#include <cmath>

// //
bool isCollision(float x1, float y1, float w1, float h1,
                 float x2, float y2, float w2, float h2 );

bool isCollision(sf::Vector2f pos, sf::Vector2f size,
                 sf::Vector2f pos2, sf::Vector2f size2 );
// //


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
      // ADDING NEW BITCOINS, STONES, BONUSES
      addBitcoin(bitcoin_timer);
      addEnemy(enemy_timer);
      addBonus(bonus_timer);
      
      updatePlayer();
      updateBitcoins();
      updateEnemies();
      updateBonuses();
      updateActiveBonuses();

      if(sin_clock.getElapsedTime().asMilliseconds() > sin_time)
	{
	  sin_amplitude = -sin_amplitude;
	  t_btc_falling.setRotation(0);
	  t_enemy_falling.setRotation(0);
	  sin_clock.restart();
	}

      t_btc_falling.rotate(5*sin(sin_amplitude * frame_time.asSeconds()));
      t_enemy_falling.rotate(5*sin(sin_amplitude * frame_time.asSeconds()));
    
      if(!explosion_sprite.isPlaying())
	explosion_sprite.setPosition(sf::Vector2f(-100, -100));
      explosion_sprite.update(frame_time);

      // POINTS
      std::ostringstream _score_string;
      _score_string << player.score;
	  
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

      if(click_on_start && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  enemies.clear();
	  bitcoins.clear();
	  bonuses.clear();
	  player.pos = sf::Vector2f(300,400);
	  player.score = 0;
	  state = GAME;
	  menu_music.stop();
	  game_music.play();
	}

      // Click on credits menu
      if(click_on_credits && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  state = CREDITS;
	}

      // Click on exit menu
      if(click_on_exit && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  window.close();
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
    }
  else if(state == CREDITS)
    {
      b_back.setPosition(sf::Vector2f(500,500));
      t_credits.setPosition(sf::Vector2f(100,150));

      sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);
      sf::Vector2f b_back_size(b_back.getLocalBounds().width, b_back.getLocalBounds().height);
      
      bool click_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				       b_back.getPosition(), b_back_size);

      if(click_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  state = MENU;
	}
    }
}

void App::updateBitcoins()
{
  for(std::size_t i = 0; i < bitcoins.size(); i++)
    {
      bitcoins[i].pos.y += bitcoins[i].vel;
	  
      bool collision_with_player = isCollision(player.pos.x, player.pos.y, 96, 64,
					       bitcoins[i].pos.x, bitcoins[i].pos.y, 32, 32);

      if(bitcoins[i].pos.y > 600 || collision_with_player)
	{
	  if(collision_with_player)
	    {
	      player.score += bitcoins[i].points;
	      btc_sound.play();
	    }

	  bitcoins.erase(bitcoins.begin() + i);
	}
    }
}

void App::updateEnemies()
{
  for(std::size_t i = 0; i < enemies.size(); i++)
    {
      enemies[i].pos.y += enemies[i].vel;

      bool collision_with_player = isCollision(player.pos.x, player.pos.y, 96, 64,
					       enemies[i].pos.x, enemies[i].pos.y, 32, 32);

      if(collision_with_player)
	{
	  state = SCORE;
	  score_music.play();
	  game_music.stop();
	}

      if(enemies[i].pos.y > 600)
	{
	  enemies.erase(enemies.begin() + i);
	}
    }
}

void App::updatePlayer()
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    player.pos.y -= 6;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    player.pos.y += 6;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    player.pos.x -= 6;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    player.pos.x += 6;

  if(player.pos.y > 600 - 64)
    player.pos.y = 600 - 64;
  if(player.pos.y < 0)
    player.pos.y = 0;
  if(player.pos.x > 800 - 96)
    player.pos.x = 800 - 96;
  if(player.pos.x < 0)
    player.pos.x = 0;
}

void App::updateBonuses()
{
  for(std::size_t i = 0; i < bonuses.size(); i++)
    {
      bonuses[i].pos.y += bonuses[i].vel;

      bool collision_with_player = isCollision(player.pos.x, player.pos.y, 96, 64,
					       bonuses[i].pos.x, bonuses[i].pos.y, 32, 32);

      if(bonuses[i].pos.y > 600 || collision_with_player)
	{
	  if(collision_with_player)
	    {
	      active_bonuses.push_back(ActiveBonus(bonuses[i].type, bonuses[i].time_working));
	      
	      if(bonuses[i].type == B_EXPLODE)
		{
		  sf::Vector2f pos = bonuses[i].pos;
		  explosion_sprite.setPosition(pos);
		  explosion_sprite.play(explosion);
		  explosion_sound.play();
		}
	    }
	  bonuses.erase(bonuses.begin() + i);
	}
    }
}

void App::updateActiveBonuses()
{

  for(std::size_t i = 0; i < active_bonuses.size(); i++)
    {
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
		std::size_t num_enemies = enemies.size();
		for(std::size_t i = 0; i < num_enemies; i++)
		  {
		    sf::Vector2f pos = enemies[i].pos;
		    float vel = enemies[i].vel;
		    float points = rand() % 20 + 1;
		    Bitcoin btc(pos, vel, points);
		    bitcoins.push_back(btc);
		    enemies.erase(enemies.begin() + i);
		  }
	      }
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
	    default:
	      break;
	    }
	  active_bonuses.erase(active_bonuses.begin() + i);
	}
    }
}

void App::addBitcoin(float milliseconds)
{
  if(bitcoin_clock.getElapsedTime().asMilliseconds() > milliseconds)
    {
      bitcoins.push_back(Bitcoin(sf::Vector2f(rand()%760+1, -32), rand()%5+1, rand()%20+1));
      bitcoin_clock.restart();
    }
}

void App::addEnemy(float milliseconds)
{
  if(enemy_clock.getElapsedTime().asMilliseconds() > milliseconds)
    {
      enemies.push_back(Enemy(sf::Vector2f(rand()%760+1, -32), rand()%5+1));
      enemy_clock.restart();
    }
}

void App::addBonus(float milliseconds)
{
  if(bonus_clock.getElapsedTime().asMilliseconds() > milliseconds)
    {
      int rand_bonus = rand()%3+1;
      BONUS_TYPE type;
      switch(rand_bonus)
	{
	case 1:
	  type = B_DOUBLE_BTC;
	  break;
	case 2:
	  type = B_DOUBLE_ENEMIES;
	  break;
	case 3:
	  type = B_EXPLODE;
	  break;
	}
      bonuses.push_back(Bonus(sf::Vector2f(rand()%760+1, -32), rand()%5+1, type, 2000));
      bonus_clock.restart();
    }
}

// // //
bool isCollision(float x1, float y1, float w1, float h1,
                 float x2, float y2, float w2, float h2 )
{
  if( x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2 )
    return( true );
  return( false );
}

bool isCollision(sf::Vector2f pos, sf::Vector2f size,
                 sf::Vector2f pos2, sf::Vector2f size2 )
{
  if( pos.x + size.x >= pos2.x && pos.x <= pos2.x + size2.x &&
      pos.y + size.y >= pos2.y && pos.y <= pos2.y + size2.y )
    return( true );
  return( false );
}
