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
      for(auto i : explosion_sprites)
	{
	  window.draw(i);
	}
      window.draw(small_explosion_sprite);
      window.draw(bonus_animation_sprite);
      s_wallet.setPosition(player.getPosition());
      window.draw(s_wallet);
      if(show_t_darkness) // HACK - using bool used to text
	window.draw( s_lighting, sf::BlendMultiply );
      if(show_t_btc_falling)
	window.draw(t_btc_falling);
      if(show_t_enemy_falling)
	window.draw(t_enemy_falling);
      if(show_t_explosion)
	window.draw(t_explosion);
      if(show_t_keys)
	window.draw(t_keys);
      if(show_t_darkness)
	window.draw(t_darkness);
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
      window.draw(s_credits_background);
      window.draw(t_score);
      window.draw(b_back);
      window.display();
    }
  else if(state == CREDITS)
    {
      window.clear();
      window.draw(s_credits_background);
      window.draw(t_credits);
      window.draw(b_back);
      window.display();
    }
  else if(state == RESUME)
    {
      window.clear();
      window.draw(s_menu_background);
      window.draw(b_resume);
      window.draw(b_menu);
      window.display();
    }
}
