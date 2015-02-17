#include <app.h>

void App::updateMainShop()
{
  static sf::Clock shop_clock;
  static sf::Time shop_time;
  static float click_time = 0;

  shop_time = shop_clock.restart();
  click_time += shop_time.asSeconds();

  sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);

  bool mouse_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				   shop_texts.getText("btn_back").text().getPosition(),
				   shop_texts.getText("btn_back").getSizeOfText());

  bool mouse_on_playerskins = isCollision(mouse_position, sf::Vector2f(1,1),
					  shop_texts.getText("btn_playerskins").text().getPosition(),
					  shop_texts.getText("btn_playerskins").getSizeOfText());

  bool mouse_on_enemyskins = isCollision(mouse_position, sf::Vector2f(1,1),
					 shop_texts.getText("btn_enemyskins").text().getPosition(),
					 shop_texts.getText("btn_enemyskins").getSizeOfText());
      

  if(mouse_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2)
    {
      state = MENU;
      click_time = 0;
    }

  if(mouse_on_playerskins && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2)
    {
      shop_state = PLAYERSHOP;
      click_time = 0;
    }

  if(mouse_on_enemyskins && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2)
    {
      shop_state = ENEMYSHOP;
      click_time = 0;
    }
}

