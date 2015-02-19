#include <app.h>

void App::updateScore()
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
