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
      s_enemy.rotate(5);
      for(auto st : enemies)
	{
	  s_enemy.setPosition(sf::Vector2f(st.getPosition().x + 16, st.getPosition().y + 16));
	  window.draw(s_enemy);
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
      if(player.getDirection() == 0)
	{
	  s_wallet_left.setPosition(player.getPosition());
	  window.draw(s_wallet_left);
	}
      else if(player.getDirection() == 1)
	{
	  s_wallet.setPosition(player.getPosition());
	  window.draw(s_wallet);
	}
      if(texts.getText("txt_darkness").isVisible()) // HACK - using bool used to text
	window.draw( s_lighting, sf::BlendMultiply );
      window.draw(texts.getText("txt_btc_falling"));
      window.draw(texts.getText("txt_enemy_falling"));
      window.draw(texts.getText("txt_explosion"));
      window.draw(texts.getText("txt_inverted_keys"));
      window.draw(texts.getText("txt_darkness"));
      window.draw(texts.getText("score"));
      window.display();
    }
  else if(state == MENU)
    {
      window.clear();
      window.draw(s_menu_background);
      window.draw(texts.getText("btn_start"));
      window.draw(texts.getText("btn_credits"));
      window.draw(texts.getText("btn_exit"));
      window.display();
    }
  else if(state == SCORE)
    {  
      window.clear();
      window.draw(s_credits_background);
      window.draw(texts.getText("score"));
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
}
