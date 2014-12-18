#include <app.h>

void App::draw()
{
  if(state == GAME)
    {
      window.clear();
      window.draw(s_game_background);
      for(auto btc : bitcoins)
	{
	  s_btc.setPosition(btc.pos);
	  window.draw(s_btc);
	}
      s_enemy.setOrigin(sf::Vector2f(16,16));
      s_enemy.rotate(5);
      for(auto st : enemies)
	{
	  s_enemy.setPosition(sf::Vector2f(st.pos.x + 16, st.pos.y + 16));
	  window.draw(s_enemy);
	}
      for(auto i : bonuses)
	{
	  switch(i.type)
	    {
	    case B_DOUBLE_BTC:
	      s_double_btc_bonus.setPosition(i.pos);
	      window.draw(s_double_btc_bonus);
	      break;
	    case B_DOUBLE_ENEMIES:
	      s_double_enemy_bonus.setPosition(i.pos);
	      window.draw(s_double_enemy_bonus);
	      break;
	    case B_EXPLODE:
	      s_explode_bonus.setPosition(i.pos);
	      window.draw(s_explode_bonus);
	      break;
	    }
	}
      if(show_t_btc_falling)
	window.draw(t_btc_falling);
      if(show_t_enemy_falling)
	window.draw(t_enemy_falling);
      window.draw(explosion_sprite);
      s_wallet.setPosition(player.pos);
      window.draw(s_wallet);
      window.draw(t_score);
      window.display();
    }
  else if(state == MENU)
    {
      window.clear();
      window.draw(s_menu_background);
      window.draw(b_start);
      window.draw(b_credits);
      window.draw(b_exit);
      window.display();
    }
  else if(state == SCORE)
    {  
      window.clear();
      window.draw(t_score);
      window.draw(b_back);
      window.display();
    }
  else if(state == CREDITS)
    {
      window.clear();
      window.draw(t_credits);
      window.draw(b_back);
      window.display();
    }
}
