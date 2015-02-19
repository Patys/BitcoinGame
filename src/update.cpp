#include <app.h>


void App::update()
{

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

  frame_time = frame_clock.restart();

  texts.update(frame_time.asSeconds());

  std::ostringstream _score_string;
  _score_string << game_score;
  texts.getText("game_score").text().setString("Bitcoins: " + _score_string.str());
  texts.getText("game_score").text().setOrigin(texts.getText("game_score").getCenterOfText());


  if(state == GAME)
    {
      updateGame();
    }
  //MENU
  else if(state == MENU)
    {
      updateMenu();
    }
  // SCORE
  else if(state == SCORE)
    {
      updateScore();
    }
  else if(state == CREDITS)
    {
      updateCredits();
    }
  else if(state == RESUME)
    {
      updateResume();
    }
  else if(state == SHOP) // SHOP LOGIC
    {
      checkSettings();
      updateShop();
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

  checkSettings();

  texts.getText("txt_btc_falling").hide();
  texts.getText("txt_enemy_falling").hide();
  texts.getText("txt_explosion").hide();
  texts.getText("txt_inverted_keys").hide();
  texts.getText("txt_darkness").hide();
}
