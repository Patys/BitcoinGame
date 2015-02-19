#include <app.h>

void App::updateResume()
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
