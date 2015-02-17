#include <app.h>

void App::drawShop()
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
