#include <app.h>

void App::draw()
{
  if(state == GAME)
    {
      window.clear();
      window.draw(s_game_background);
      for(auto btc : bitcoins)
	{
	  s_btc.setPosition(btc.getPosition());
	  window.draw(s_btc);
	}
      s_enemy.setOrigin(sf::Vector2f(16,16));
      if(setting_skins.getCurrentEnemySkin() == ES_SKIN2 ||
	 setting_skins.getCurrentEnemySkin() == ES_SKIN5 ||
	 setting_skins.getCurrentEnemySkin() == ES_SKIN7)
	{
	  s_enemy.rotate(5);
	}
      for(auto st : enemies)
	{
	  s_enemy.setPosition(sf::Vector2f(st.getPosition().x + 16, st.getPosition().y + 16));
	  window.draw(s_enemy);
	}
      if(speed_enemy)
	{
	  s_warning.setPosition(sf::Vector2f(speed_enemy_position.x, 0));
	  window.draw(s_warning);
	}
      for(auto i : bonuses)
	{
	  s_bonus.setPosition(i.pos);
	  window.draw(s_bonus);
	}
      for(auto i : baloons)
	{
	  s_baloon.setPosition(sf::Vector2f(i.getPosition().x+12, i.getPosition().y));
	  window.draw(s_baloon);
	}
      for(auto i : explosion_sprites)
	{
	  window.draw(i);
	}
      window.draw(small_explosion_sprite);

      if(player.isControl())
	{
	  s_wallet.setPosition(player.getPosition());
	  window.draw(s_wallet);
	}
      else
	{
	  s_wallet_dead.setPosition(player.getPosition());
	  window.draw(s_wallet_dead);
	}
      if(player.isImmortality() && !immortalityIsEnding() )
	{
	  s_bonus_immortality.setPosition(player.getPosition() + sf::Vector2f(-10,-40));
	  window.draw(s_bonus_immortality);
	}

      for(auto btc : end_game_bitcoins)
	{
	  s_bloody_btc.setPosition(btc.getPosition());
	  window.draw(s_bloody_btc);
	}

      if(texts.getText("txt_darkness").isVisible()) // HACK - using bool used to text
	window.draw( s_lighting, sf::BlendMultiply );
      window.draw(texts.getText("txt_btc_falling"));
      window.draw(texts.getText("txt_enemy_falling"));
      window.draw(texts.getText("txt_explosion"));
      window.draw(texts.getText("txt_inverted_keys"));
      window.draw(texts.getText("txt_darkness"));
      window.draw(texts.getText("t_die"));
      window.draw(texts.getText("score"));
      window.display();
    }
  else if(state == MENU)
    {
      window.clear();
      window.draw(s_menu_background);
      window.draw(texts.getText("btn_start"));
      window.draw(texts.getText("btn_shop"));
      window.draw(texts.getText("btn_credits"));
      window.draw(texts.getText("btn_exit"));
      window.draw(texts.getText("game_score"));
      window.display();
    }
  else if(state == SCORE)
    {  
      window.clear();
      window.draw(s_credits_background);
      window.draw(texts.getText("score"));
      window.draw(texts.getText("game_score"));
      window.draw(texts.getText("btn_back"));
      window.draw(texts.getText("btn_restart"));
      window.draw(texts.getText("tip_text"));
      window.draw(texts.getText("tip"));
      window.display();
    }
  else if(state == CREDITS)
    {
      window.clear();
      window.draw(s_credits_background);
      window.draw(texts.getText("txt_credits"));
      window.draw(texts.getText("btn_back"));
      window.display();
    }
  else if(state == RESUME)
    {
      window.clear();
      window.draw(s_credits_background);
      window.draw(texts.getText("btn_resume"));
      window.draw(texts.getText("btn_menu"));
      window.draw(texts.getText("tip_text"));
      window.draw(texts.getText("tip"));
      window.display();
    }
  else if(state == SHOP)
    {
      window.clear();
      window.draw(s_game_background);
      window.draw(texts.getText("game_score"));
      if(shop_state == MAINSHOP)
	{
	  window.draw(shop_texts.getText("btn_playerskins"));
	  window.draw(shop_texts.getText("btn_enemyskins"));
	  window.draw(shop_texts.getText("btn_back"));
	}
      if(shop_state == PLAYERSHOP)
	{
	  window.draw(shop_texts.getText("ps_name_skin1"));
	  window.draw(shop_texts.getText("ps_des_skin1"));

	  window.draw(shop_texts.getText("ps_name_skin2"));
	  window.draw(shop_texts.getText("ps_des_skin2"));

	  window.draw(shop_texts.getText("ps_name_skin3"));
	  window.draw(shop_texts.getText("ps_des_skin3"));

	  window.draw(shop_texts.getText("ps_name_skin4"));
	  window.draw(shop_texts.getText("ps_des_skin4"));

	  window.draw(shop_texts.getText("ps_name_skin5"));
	  window.draw(shop_texts.getText("ps_des_skin5"));

	  window.draw(shop_texts.getText("ps_name_skin6"));
	  window.draw(shop_texts.getText("ps_des_skin6"));

	  window.draw(shop_texts.getText("ps_name_skin7"));
	  window.draw(shop_texts.getText("ps_des_skin7"));

	  window.draw(shop_texts.getText("ps_name_skin8"));
	  window.draw(shop_texts.getText("ps_des_skin8"));

	  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet1.png"));
	  s_wallet.setPosition(sf::Vector2f(100,20));
	  window.draw(s_wallet);

	  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet2.png"));
	  s_wallet.setPosition(sf::Vector2f(250,20));
	  window.draw(s_wallet);

	  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet3.png"));
	  s_wallet.setPosition(sf::Vector2f(400,20));
	  window.draw(s_wallet);

	  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet4.png"));
	  s_wallet.setPosition(sf::Vector2f(550,20));
	  window.draw(s_wallet);

	  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet5.png"));
	  s_wallet.setPosition(sf::Vector2f(100,300));
	  window.draw(s_wallet);

	  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet6.png"));
	  s_wallet.setPosition(sf::Vector2f(250,300));
	  window.draw(s_wallet);

	  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet7.png"));
	  s_wallet.setPosition(sf::Vector2f(400,300));
	  window.draw(s_wallet);

	  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet8.png"));
	  s_wallet.setPosition(sf::Vector2f(550,300));
	  window.draw(s_wallet);

	  window.draw(select_rectangle);

	  window.draw(shop_texts.getText("btn_back"));

	  if(setting_skins.getCurrentPlayerSkin() != select_player_skin)
	    {
	      if(setting_skins.isOwnedPlayerSkin(select_player_skin))
		window.draw(shop_texts.getText("btn_equip"));
	      else window.draw(shop_texts.getText("btn_buy"));
	    }
	}
      if(shop_state == ENEMYSHOP)
	{
	  window.draw(shop_texts.getText("es_name_skin1"));
	  window.draw(shop_texts.getText("es_des_skin1"));

	  window.draw(shop_texts.getText("es_name_skin2"));
	  window.draw(shop_texts.getText("es_des_skin2"));

	  window.draw(shop_texts.getText("es_name_skin3"));
	  window.draw(shop_texts.getText("es_des_skin3"));

	  window.draw(shop_texts.getText("es_name_skin4"));
	  window.draw(shop_texts.getText("es_des_skin4"));

	  window.draw(shop_texts.getText("es_name_skin5"));
	  window.draw(shop_texts.getText("es_des_skin5"));

	  window.draw(shop_texts.getText("es_name_skin6"));
	  window.draw(shop_texts.getText("es_des_skin6"));

	  window.draw(shop_texts.getText("es_name_skin7"));
	  window.draw(shop_texts.getText("es_des_skin7"));

	  window.draw(shop_texts.getText("es_name_skin8"));
	  window.draw(shop_texts.getText("es_des_skin8"));

	  s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy1.png"));
	  s_enemy.setPosition(sf::Vector2f(100,20));
	  window.draw(s_enemy);

	  s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy2.png"));
	  s_enemy.setPosition(sf::Vector2f(250,20));
	  window.draw(s_enemy);

	  s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy3.png"));
	  s_enemy.setPosition(sf::Vector2f(400,20));
	  window.draw(s_enemy);

	  s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy4.png"));
	  s_enemy.setPosition(sf::Vector2f(550,20));
	  window.draw(s_enemy);

	  s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy5.png"));
	  s_enemy.setPosition(sf::Vector2f(100,300));
	  window.draw(s_enemy);

	  s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy6.png"));
	  s_enemy.setPosition(sf::Vector2f(250,300));
	  window.draw(s_enemy);

	  s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy7.png"));
	  s_enemy.setPosition(sf::Vector2f(400,300));
	  window.draw(s_enemy);

	  s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy8.png"));
	  s_enemy.setPosition(sf::Vector2f(550,300));
	  window.draw(s_enemy);

	  window.draw(select_rectangle);

	  if(setting_skins.getCurrentEnemySkin() != select_enemy_skin)
	    {
	      if(setting_skins.isOwnedEnemySkin(select_enemy_skin))
		window.draw(shop_texts.getText("btn_equip"));
	      else window.draw(shop_texts.getText("btn_buy"));
	    }

	  window.draw(shop_texts.getText("btn_back"));
	}
      window.display();
    }
}
