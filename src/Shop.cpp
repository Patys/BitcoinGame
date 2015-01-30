#include <app.h>

enum SHOPSTATE { MAINSHOP, PLAYERSHOP, ENEMYSHOP };

SHOPSTATE shop_state;

Shop::Shop(): texts()
{
  shop_state = MAINSHOP;
}

void Shop::init(App* app)
{
  createPlayerSkin(app, "skin1", "Basic", "Simple wallet.", PS_SKIN1);
  texts.getText("ps_name_skin1").text().setPosition(100,120);
  texts.getText("ps_des_skin1").text().setPosition(100,150);

  createPlayerSkin(app, "skin2", "Happy Wallet", "Happy wallet\nwith nice smile.\nCost:20", PS_SKIN2);
  texts.getText("ps_name_skin2").text().setPosition(250,120);
  texts.getText("ps_des_skin2").text().setPosition(250,150);

  createPlayerSkin(app, "skin3", "Kitty Wallet", "Wallet looks\nlike a cat.\nCost: 30", PS_SKIN3);
  texts.getText("ps_name_skin3").text().setPosition(400,120);
  texts.getText("ps_des_skin3").text().setPosition(400,150);

  createPlayerSkin(app, "skin4", "Ninja Wallet", "Wallet\nmade only\nfor ninja.\nCost: 40", PS_SKIN4);
  texts.getText("ps_name_skin4").text().setPosition(550,120);
  texts.getText("ps_des_skin4").text().setPosition(550,150);

  createPlayerSkin(app, "skin5", "Vampire Wallet", "Vampire\nwants\nmore bitcoins.\nCost: 50", PS_SKIN5);
  texts.getText("ps_name_skin5").text().setPosition(100,390);
  texts.getText("ps_des_skin5").text().setPosition(100,420);

  createPlayerSkin(app, "skin6", "Pirat Wallet", "Pirates\nflow on\nbitcoins.\nCost: 60", PS_SKIN6);
  texts.getText("ps_name_skin6").text().setPosition(250,390);
  texts.getText("ps_des_skin6").text().setPosition(250,420);

  createPlayerSkin(app, "skin7", "Creazy Wallet", "Creazy!\nI want more\nbitcoins!.\nCost: 70", PS_SKIN7);
  texts.getText("ps_name_skin7").text().setPosition(400,390);
  texts.getText("ps_des_skin7").text().setPosition(400,420);

  createPlayerSkin(app, "skin8", "Smart Wallet", "Wallet\nfull of\nknowledge.\nCost: 80", PS_SKIN8);
  texts.getText("ps_name_skin8").text().setPosition(550,390);
  texts.getText("ps_des_skin8").text().setPosition(550,420);

  createEnemySkin(app, "skin1", "Stone", "Stones come\nfrom heaven.", ES_SKIN1);
  texts.getText("es_name_skin1").text().setPosition(100,120);
  texts.getText("es_des_skin1").text().setPosition(100,150);

  createEnemySkin(app, "skin2", "Shuriken", "Deadly shurkiens\nare attacking.\nCost: 20", ES_SKIN2);
  texts.getText("es_name_skin2").text().setPosition(250,120);
  texts.getText("es_des_skin2").text().setPosition(250,150);

  createEnemySkin(app, "skin3", "Chest", "Careful!\nChests\nfalling down.\nCost: 30", ES_SKIN3);
  texts.getText("es_name_skin3").text().setPosition(400,120);
  texts.getText("es_des_skin3").text().setPosition(400,150);

  createEnemySkin(app, "skin4", "Flowerpot", "Angry man\nthrows\nflowerpots.\nCost: 40", ES_SKIN4);
  texts.getText("es_name_skin4").text().setPosition(550,120);
  texts.getText("es_des_skin4").text().setPosition(550,150);

  createEnemySkin(app, "skin5", "Deadly ball", "Ball which\nkill\neverybody.\nCost: 50", ES_SKIN5);
  texts.getText("es_name_skin5").text().setPosition(100,420);
  texts.getText("es_des_skin5").text().setPosition(100,450);

  createEnemySkin(app, "skin6", "Stalagmite", "Stalagmites\nare in caves.\nCareful!\nCost: 60", ES_SKIN6);
  texts.getText("es_name_skin6").text().setPosition(250,420);
  texts.getText("es_des_skin6").text().setPosition(250,450);

  createEnemySkin(app, "skin7", "Hammer", "Hammers\nare very\ndangerous!\nCost: 70", ES_SKIN7);
  texts.getText("es_name_skin7").text().setPosition(400,420);
  texts.getText("es_des_skin7").text().setPosition(400,450);

  createEnemySkin(app, "skin8", "Meteorite", "Meteorites\nare comming\nfrom space!\nCost: 80", ES_SKIN8);
  texts.getText("es_name_skin8").text().setPosition(550,420);
  texts.getText("es_des_skin8").text().setPosition(550,450);

  
  select_rectangle.setSize(sf::Vector2f(150, 260));
  select_rectangle.setFillColor(sf::Color::Transparent);
  select_rectangle.setOutlineColor(sf::Color::Transparent);
  select_rectangle.setOutlineThickness(5);
  select_rectangle.setPosition(80, 10);

  ShakingText t_back("Back", app->font1);
  t_back.text().setPosition(700,550);
  texts.addText("btn_back", t_back);

  ShakingText t_buy("Buy", app->font1);
  t_buy.text().setPosition(25,550);
  texts.addText("btn_buy", t_buy);

  ShakingText t_equip("Equip", app->font1);
  t_equip.text().setPosition(25,550);
  texts.addText("btn_equip", t_equip);

  ShakingText t_playerskin("Player Skins", app->font1);
  t_playerskin.text().setPosition(200,200);
  texts.addText("btn_playerskins", t_playerskin);

  ShakingText t_enemyskin("Enemy Skins", app->font1);
  t_enemyskin.text().setPosition(200,250);
  texts.addText("btn_enemyskins", t_enemyskin);

  shop_state = MAINSHOP;
  select_player_skin = PS_SKIN1;
  select_enemy_skin = ES_SKIN1;
}

void Shop::update(App* app)
{
  sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(app->window);

  static sf::Clock shop_clock;
  sf::Time shop_time = shop_clock.restart();

  static float click_time = 0;
  click_time += shop_time.asSeconds();

  texts.update(0.016);

  app->s_wallet.setRotation(0);
  app->s_enemy.setRotation(0);

  if(shop_state == MAINSHOP)
    {
      bool mouse_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_back").text().getPosition(),
				       texts.getText("btn_back").getSizeOfText());
      
      bool mouse_on_playerskins = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_playerskins").text().getPosition(),
				       texts.getText("btn_playerskins").getSizeOfText());
      
      bool mouse_on_enemyskins = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_enemyskins").text().getPosition(),
				       texts.getText("btn_enemyskins").getSizeOfText());
      
      if(mouse_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2)
	{
	  app->state = MENU;
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
  if(shop_state == PLAYERSHOP)
    {
      bool mouse_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_back").text().getPosition(),
				       texts.getText("btn_back").getSizeOfText());

      bool mouse_on_buy = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_buy").text().getPosition(),
				       texts.getText("btn_buy").getSizeOfText());

      bool mouse_on_equip = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_equip").text().getPosition(),
				       texts.getText("btn_equip").getSizeOfText());

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

      if(app->setting_skins.isOwnedPlayerSkin(select_player_skin))
	{
	  select_rectangle.setOutlineColor(sf::Color::Green);
	  if(app->setting_skins.getCurrentPlayerSkin() == select_player_skin)
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
	 !app->setting_skins.isOwnedPlayerSkin(select_player_skin))
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
	  if(app->game_score >= cost)
	    {
	      app->setGameScore(app->game_score - cost);
	      app->setting_skins.addPlayerSkin(select_player_skin);
	    }
	  click_time = 0;
	}

      if(mouse_on_equip && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2 &&
	 app->setting_skins.isOwnedPlayerSkin(select_player_skin) && 
	 app->setting_skins.getCurrentPlayerSkin() != select_player_skin)
	{
	  app->setting_skins.setPlayerSkin(select_player_skin);
	  click_time = 0;
	}

    }
  if(shop_state == ENEMYSHOP)
    {
      bool mouse_on_back = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_back").text().getPosition(),
				       texts.getText("btn_back").getSizeOfText());


      bool mouse_on_buy = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_buy").text().getPosition(),
				       texts.getText("btn_buy").getSizeOfText());

      bool mouse_on_equip = isCollision(mouse_position, sf::Vector2f(1,1),
				       texts.getText("btn_equip").text().getPosition(),
				       texts.getText("btn_equip").getSizeOfText());

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


      if(app->setting_skins.isOwnedEnemySkin(select_enemy_skin))
	{
	  select_rectangle.setOutlineColor(sf::Color::Green);
	  if(app->setting_skins.getCurrentEnemySkin() == select_enemy_skin)
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
	 !app->setting_skins.isOwnedEnemySkin(select_enemy_skin))
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
	  if(app->game_score >= cost)
	    {
	      app->setGameScore(app->game_score - cost);
	      app->setting_skins.addEnemySkin(select_enemy_skin);
	    }
	  click_time = 0;
	}

      if(mouse_on_equip && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2 &&
	 app->setting_skins.isOwnedEnemySkin(select_enemy_skin) && 
	 app->setting_skins.getCurrentEnemySkin() != select_enemy_skin)
	{
	  app->setting_skins.setEnemySkin(select_enemy_skin);
	  click_time = 0;
	}

      if(mouse_on_back && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_time > 0.2)
	{
	  shop_state = MAINSHOP;
	  click_time = 0;
	}
    }
}

void Shop::draw(App* app)
{
  
  if(shop_state == MAINSHOP)
    {
      
      app->window.draw(texts.getText("btn_playerskins"));
      app->window.draw(texts.getText("btn_enemyskins"));
      app->window.draw(texts.getText("btn_back"));
    }
  if(shop_state == PLAYERSHOP)
    {
      app->window.draw(texts.getText("ps_name_skin1"));
      app->window.draw(texts.getText("ps_des_skin1"));

      app->window.draw(texts.getText("ps_name_skin2"));
      app->window.draw(texts.getText("ps_des_skin2"));

      app->window.draw(texts.getText("ps_name_skin3"));
      app->window.draw(texts.getText("ps_des_skin3"));

      app->window.draw(texts.getText("ps_name_skin4"));
      app->window.draw(texts.getText("ps_des_skin4"));

      app->window.draw(texts.getText("ps_name_skin5"));
      app->window.draw(texts.getText("ps_des_skin5"));

      app->window.draw(texts.getText("ps_name_skin6"));
      app->window.draw(texts.getText("ps_des_skin6"));

      app->window.draw(texts.getText("ps_name_skin7"));
      app->window.draw(texts.getText("ps_des_skin7"));

      app->window.draw(texts.getText("ps_name_skin8"));
      app->window.draw(texts.getText("ps_des_skin8"));

      app->s_wallet.setTexture(app->tex_menager.getTexture("data/graphics/wallet1.png"));
      app->s_wallet.setPosition(sf::Vector2f(100,20));
      app->window.draw(app->s_wallet);

      app->s_wallet.setTexture(app->tex_menager.getTexture("data/graphics/wallet2.png"));
      app->s_wallet.setPosition(sf::Vector2f(250,20));
      app->window.draw(app->s_wallet);

      app->s_wallet.setTexture(app->tex_menager.getTexture("data/graphics/wallet3.png"));
      app->s_wallet.setPosition(sf::Vector2f(400,20));
      app->window.draw(app->s_wallet);

      app->s_wallet.setTexture(app->tex_menager.getTexture("data/graphics/wallet4.png"));
      app->s_wallet.setPosition(sf::Vector2f(550,20));
      app->window.draw(app->s_wallet);

      app->s_wallet.setTexture(app->tex_menager.getTexture("data/graphics/wallet5.png"));
      app->s_wallet.setPosition(sf::Vector2f(100,300));
      app->window.draw(app->s_wallet);

      app->s_wallet.setTexture(app->tex_menager.getTexture("data/graphics/wallet6.png"));
      app->s_wallet.setPosition(sf::Vector2f(250,300));
      app->window.draw(app->s_wallet);

      app->s_wallet.setTexture(app->tex_menager.getTexture("data/graphics/wallet7.png"));
      app->s_wallet.setPosition(sf::Vector2f(400,300));
      app->window.draw(app->s_wallet);

      app->s_wallet.setTexture(app->tex_menager.getTexture("data/graphics/wallet8.png"));
      app->s_wallet.setPosition(sf::Vector2f(550,300));
      app->window.draw(app->s_wallet);
      
      app->window.draw(select_rectangle);

      app->window.draw(texts.getText("btn_back"));

      if(app->setting_skins.getCurrentPlayerSkin() != select_player_skin)
	{
	  if(app->setting_skins.isOwnedPlayerSkin(select_player_skin))
	    app->window.draw(texts.getText("btn_equip"));
	  else app->window.draw(texts.getText("btn_buy"));
	}
    }
  if(shop_state == ENEMYSHOP)
    {
      app->window.draw(texts.getText("es_name_skin1"));
      app->window.draw(texts.getText("es_des_skin1"));

      app->window.draw(texts.getText("es_name_skin2"));
      app->window.draw(texts.getText("es_des_skin2"));

      app->window.draw(texts.getText("es_name_skin3"));
      app->window.draw(texts.getText("es_des_skin3"));

      app->window.draw(texts.getText("es_name_skin4"));
      app->window.draw(texts.getText("es_des_skin4"));

      app->window.draw(texts.getText("es_name_skin5"));
      app->window.draw(texts.getText("es_des_skin5"));

      app->window.draw(texts.getText("es_name_skin6"));
      app->window.draw(texts.getText("es_des_skin6"));

      app->window.draw(texts.getText("es_name_skin7"));
      app->window.draw(texts.getText("es_des_skin7"));

      app->window.draw(texts.getText("es_name_skin8"));
      app->window.draw(texts.getText("es_des_skin8"));

      app->s_enemy.setTexture(app->tex_menager.getTexture("data/graphics/enemy1.png"));
      app->s_enemy.setPosition(sf::Vector2f(100,20));
      app->window.draw(app->s_enemy);

      app->s_enemy.setTexture(app->tex_menager.getTexture("data/graphics/enemy2.png"));
      app->s_enemy.setPosition(sf::Vector2f(250,20));
      app->window.draw(app->s_enemy);

      app->s_enemy.setTexture(app->tex_menager.getTexture("data/graphics/enemy3.png"));
      app->s_enemy.setPosition(sf::Vector2f(400,20));
      app->window.draw(app->s_enemy);

      app->s_enemy.setTexture(app->tex_menager.getTexture("data/graphics/enemy4.png"));
      app->s_enemy.setPosition(sf::Vector2f(550,20));
      app->window.draw(app->s_enemy);

      app->s_enemy.setTexture(app->tex_menager.getTexture("data/graphics/enemy5.png"));
      app->s_enemy.setPosition(sf::Vector2f(100,300));
      app->window.draw(app->s_enemy);

      app->s_enemy.setTexture(app->tex_menager.getTexture("data/graphics/enemy6.png"));
      app->s_enemy.setPosition(sf::Vector2f(250,300));
      app->window.draw(app->s_enemy);

      app->s_enemy.setTexture(app->tex_menager.getTexture("data/graphics/enemy7.png"));
      app->s_enemy.setPosition(sf::Vector2f(400,300));
      app->window.draw(app->s_enemy);

      app->s_enemy.setTexture(app->tex_menager.getTexture("data/graphics/enemy8.png"));
      app->s_enemy.setPosition(sf::Vector2f(550,300));
      app->window.draw(app->s_enemy);

      app->window.draw(select_rectangle);

      if(app->setting_skins.getCurrentEnemySkin() != select_enemy_skin)
	{
	  if(app->setting_skins.isOwnedEnemySkin(select_enemy_skin))
	    app->window.draw(texts.getText("btn_equip"));
	  else app->window.draw(texts.getText("btn_buy"));
	}

      app->window.draw(texts.getText("btn_back"));
    }
}

void Shop::createPlayerSkin(App* app, const std::string& id,
			    const std::string& name, const std::string& des, PLAYERSKINS type)
{
  PlayerSkin ps_skin;
  ps_skin.setName(name);
  ps_skin.setDescription(des);
  ps_skin.setType(type);
  skins.push_back(&ps_skin);

  ShakingText t_name(skins.back()->getName(), app->font1, 18);
  texts.addText("ps_name_" + id, t_name);

  ShakingText t_des(skins.back()->getDescription(), app->font1, 16);
  texts.addText("ps_des_" + id, t_des);
}

void Shop::createEnemySkin(App* app, const std::string& id,
			   const std::string& name, const std::string& des, ENEMYSKINS type)
{
  EnemySkin es_skin;
  es_skin.setName(name);
  es_skin.setDescription(des);
  es_skin.setType(type);
  skins.push_back(&es_skin);

  ShakingText t_name(skins.back()->getName(), app->font1, 18);
  texts.addText("es_name_" + id, t_name);

  ShakingText t_des(skins.back()->getDescription(), app->font1, 16);
  texts.addText("es_des_" + id, t_des);
}
