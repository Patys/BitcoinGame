#include <app.h>

void App::updateEnemyShop()
{
  sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);

  static sf::Clock shop_clock;
  static sf::Time shop_time;
  static float click_time = 0;

  shop_time = shop_clock.restart();
  click_time += shop_time.asSeconds();

  bool mouse_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				   shop_texts.getText("btn_back").text().getPosition(),
				   shop_texts.getText("btn_back").getSizeOfText());


  bool mouse_on_buy = isCollision(mouse_position, sf::Vector2f(1,1),
				  shop_texts.getText("btn_buy").text().getPosition(),
				  shop_texts.getText("btn_buy").getSizeOfText());

  bool mouse_on_equip = isCollision(mouse_position, sf::Vector2f(1,1),
				    shop_texts.getText("btn_equip").text().getPosition(),
				    shop_texts.getText("btn_equip").getSizeOfText());

  bool mouse_on_enemy1 = isCollision(mouse_position, sf::Vector2f(1,1),
				     sf::Vector2f(80,10), sf::Vector2f(140,260));

  bool mouse_on_enemy2 = isCollision(mouse_position, sf::Vector2f(1,1),
				     sf::Vector2f(230,10), sf::Vector2f(140,260));

  bool mouse_on_enemy3 = isCollision(mouse_position, sf::Vector2f(1,1),
				     sf::Vector2f(380,10), sf::Vector2f(140,260));

  bool mouse_on_enemy4 = isCollision(mouse_position, sf::Vector2f(1,1),
				     sf::Vector2f(530,10), sf::Vector2f(140,260));

  bool mouse_on_enemy5 = isCollision(mouse_position, sf::Vector2f(1,1),
				     sf::Vector2f(80,260), sf::Vector2f(140,260));

  bool mouse_on_enemy6 = isCollision(mouse_position, sf::Vector2f(1,1),
				     sf::Vector2f(230,260), sf::Vector2f(140,260));

  bool mouse_on_enemy7 = isCollision(mouse_position, sf::Vector2f(1,1),
				     sf::Vector2f(380,260), sf::Vector2f(140,260));

  bool mouse_on_enemy8 = isCollision(mouse_position, sf::Vector2f(1,1),
				     sf::Vector2f(530,260), sf::Vector2f(140,260));


  if(setting_skins.isOwnedEnemySkin(select_enemy_skin))
    {
      select_rectangle.setOutlineColor(sf::Color::Green);
      if(setting_skins.getCurrentEnemySkin() == select_enemy_skin)
	select_rectangle.setOutlineColor(sf::Color::Yellow);
    }
  else
    select_rectangle.setOutlineColor(sf::Color::Red);

  if(mouse_on_enemy1 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(80,10);

      select_enemy_skin = ES_SKIN1;
    }

  if(mouse_on_enemy2 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(230,10);

      select_enemy_skin = ES_SKIN2;
    }

  if(mouse_on_enemy3 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(380,10);

      select_enemy_skin = ES_SKIN3;
    }

  if(mouse_on_enemy4 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(530,10);

      select_enemy_skin = ES_SKIN4;
    }

  if(mouse_on_enemy5 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(80,270);

      select_enemy_skin = ES_SKIN5;
    }

  if(mouse_on_enemy6 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(230,270);

      select_enemy_skin = ES_SKIN6;
    }

  if(mouse_on_enemy7 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(380,270);

      select_enemy_skin = ES_SKIN7;
    }

  if(mouse_on_enemy8 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(530,270);

      select_enemy_skin = ES_SKIN8;
    }

  if(mouse_on_buy && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2 &&
     !setting_skins.isOwnedEnemySkin(select_enemy_skin))
    {
      int cost = 200;
      switch(select_enemy_skin)
	{
	case ES_SKIN1:
	  cost = 20;
	  break;
	case ES_SKIN2:
	  cost = 20;
	  break;
	case ES_SKIN3:
	  cost = 30;
	  break;
	case ES_SKIN4:
	  cost = 40;
	  break;
	case ES_SKIN5:
	  cost = 50;
	  break;
	case ES_SKIN6:
	  cost = 60;
	  break;
	case ES_SKIN7:
	  cost = 70;
	  break;
	case ES_SKIN8:
	  cost = 80;
	  break;
	}
      if(game_score >= cost)
	{
	  setGameScore(game_score - cost);
	  setting_skins.addEnemySkin(select_enemy_skin);
	}
      click_time = 0;
    }

  if(mouse_on_equip && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2 &&
     setting_skins.isOwnedEnemySkin(select_enemy_skin) &&
     setting_skins.getCurrentEnemySkin() != select_enemy_skin)
    {
      setting_skins.setEnemySkin(select_enemy_skin);
      click_time = 0;
    }

  if(mouse_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2)
    {
      shop_state = MAINSHOP;
      click_time = 0;
    }
}
