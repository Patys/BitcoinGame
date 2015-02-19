#include <app.h>

void App::updateMenu()
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

  bool mouse_on_shop = isCollision(mouse_position, sf::Vector2f(1,1),
				   texts.getText("btn_shop").text().getPosition(),
				   texts.getText("btn_shop").getSizeOfText());

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
  if(mouse_on_shop && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_resume_timer > 200)
    {
      state = SHOP;
      temp_resume_timer = 0;
    }
}
