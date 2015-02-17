#include <app.h>

void updatePlayerShop()
{
  static sf::Clock shop_clock;
  static sf::Time shop_time;
  static float click_time = 0;

  shop_time = shop_clock.restart();
  click_time += shop_time.asSeconds();

  sf::Vector2f mouse_position = sf::Mouse::getPosition(window);

  bool mouse_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				   shop_texts.getText("btn_back").text().getPosition(),
				   shop_texts.getText("btn_back").getSizeOfText());

  bool mouse_on_buy = isCollision(mouse_position, sf::Vector2f(1,1),
				  shop_texts.getText("btn_buy").text().getPosition(),
				  shop_texts.getText("btn_buy").getSizeOfText());

  bool mouse_on_equip = isCollision(mouse_position, sf::Vector2f(1,1),
				    shop_texts.getText("btn_equip").text().getPosition(),
				    shop_texts.getText("btn_equip").getSizeOfText());

  bool mouse_on_wallet1 = isCollision(mouse_position, sf::Vector2f(1,1),
				      sf::Vector2f(80,10), sf::Vector2f(140,260));

  bool mouse_on_wallet2 = isCollision(mouse_position, sf::Vector2f(1,1),
				      sf::Vector2f(230,10), sf::Vector2f(140,260));

  bool mouse_on_wallet3 = isCollision(mouse_position, sf::Vector2f(1,1),
				      sf::Vector2f(380,10), sf::Vector2f(140,260));

  bool mouse_on_wallet4 = isCollision(mouse_position, sf::Vector2f(1,1),
				      sf::Vector2f(530,10), sf::Vector2f(140,260));

  bool mouse_on_wallet5 = isCollision(mouse_position, sf::Vector2f(1,1),
				      sf::Vector2f(80,260), sf::Vector2f(140,260));

  bool mouse_on_wallet6 = isCollision(mouse_position, sf::Vector2f(1,1),
				      sf::Vector2f(230,260), sf::Vector2f(140,260));

  bool mouse_on_wallet7 = isCollision(mouse_position, sf::Vector2f(1,1),
				      sf::Vector2f(380,260), sf::Vector2f(140,260));

  bool mouse_on_wallet8 = isCollision(mouse_position, sf::Vector2f(1,1),
				      sf::Vector2f(530,260), sf::Vector2f(140,260));

  if(setting_skins.isOwnedPlayerSkin(select_player_skin))
    {
      select_rectangle.setOutlineColor(sf::Color::Green);
      if(setting_skins.getCurrentPlayerSkin() == select_player_skin)
	select_rectangle.setOutlineColor(sf::Color::Yellow);
    }
  else
    select_rectangle.setOutlineColor(sf::Color::Red);

  if(mouse_on_wallet1 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(80,10);

      select_player_skin = PS_SKIN1;
    }

  if(mouse_on_wallet2 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(230,10);

      select_player_skin = PS_SKIN2;
    }

  if(mouse_on_wallet3 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(380,10);

      select_player_skin = PS_SKIN3;
    }

  if(mouse_on_wallet4 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(530,10);

      select_player_skin = PS_SKIN4;
    }

  if(mouse_on_wallet5 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(80,270);

      select_player_skin = PS_SKIN5;
    }

  if(mouse_on_wallet6 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(230,270);

      select_player_skin = PS_SKIN6;
    }

  if(mouse_on_wallet7 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(380,270);

      select_player_skin = PS_SKIN7;
    }

  if(mouse_on_wallet8 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      select_rectangle.setPosition(530,270);

      select_player_skin = PS_SKIN8;
    }


  if(mouse_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2)
    {
      shop_state = MAINSHOP;
      click_time = 0;
    }

  if(mouse_on_buy && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2 &&
     !setting_skins.isOwnedPlayerSkin(select_player_skin))
    {
      int cost = 20;
      switch(select_player_skin)
	{
	case PS_SKIN1:
	  cost = 20;
	  break;
	case PS_SKIN2:
	  cost = 20;
	  break;
	case PS_SKIN3:
	  cost = 30;
	  break;
	case PS_SKIN4:
	  cost = 40;
	  break;
	case PS_SKIN5:
	  cost = 50;
	  break;
	case PS_SKIN6:
	  cost = 60;
	  break;
	case PS_SKIN7:
	  cost = 70;
	  break;
	case PS_SKIN8:
	  cost = 80;
	  break;
	}
      if(game_score >= cost)
	{
	  setGameScore(game_score - cost);
	  setting_skins.addPlayerSkin(select_player_skin);
	}
      click_time = 0;
    }

  if(mouse_on_equip && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2 &&
     setting_skins.isOwnedPlayerSkin(select_player_skin) &&
     setting_skins.getCurrentPlayerSkin() != select_player_skin)
    {
      setting_skins.setPlayerSkin(select_player_skin);
      click_time = 0;
    }
}
