#include <app.h>

void App::updateCredits()
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
