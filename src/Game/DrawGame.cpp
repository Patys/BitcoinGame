#include <app.h>

void App::drawGame()
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
