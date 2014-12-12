#include <app.h>

void App::draw()
{
  if(state == GAME)
    {
      window.clear();
      for(auto btc : bitcoins)
	{
	  s_btc.setPosition(btc.pos);
	  window.draw(s_btc);
	}
      for(auto st : stones)
	{
	  s_stone.setPosition(st.pos);
	  window.draw(s_stone);
	}
      for(auto i : bonuses)
	{
	  switch(i.type)
	    {
	    case B_DOUBLE_BTC:
	      s_double_btc_bonus.setPosition(i.pos);
	      window.draw(s_double_btc_bonus);
	      break;
	    case B_DOUBLE_STONES:
	      s_double_stones_bonus.setPosition(i.pos);
	      window.draw(s_double_stones_bonus);
	      break;
	    case B_EXPLODE:
	      s_explode_bonus.setPosition(i.pos);
	      window.draw(s_explode_bonus);
	      break;
	    }
	}
      window.draw(explosion_sprite);
      s_wallet.setPosition(player.pos);
      window.draw(s_wallet);
      window.draw(t_score);
      window.display();
    }
  else if(state == MENU)
    {
      window.clear();
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
