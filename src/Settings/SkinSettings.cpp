#include <app.h>


void App::checkSettings()
{

  PLAYERSKINS player_skin = setting_skins.getCurrentPlayerSkin();
  switch(player_skin)
    {
    case PS_SKIN1:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet1.png"));
      break;
    case PS_SKIN2:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet2.png"));
      break;
    case PS_SKIN3:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet3.png"));
      break;
    case PS_SKIN4:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet4.png"));
      break;
    case PS_SKIN5:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet5.png"));
      break;
    case PS_SKIN6:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet6.png"));
      break;
    case PS_SKIN7:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet7.png"));
      break;
    case PS_SKIN8:
      s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet8.png"));
      break;
    }
  ENEMYSKINS enemy_skin = setting_skins.getCurrentEnemySkin();
  switch(enemy_skin)
    {
    case ES_SKIN1:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy1.png"));
      break;
    case ES_SKIN2:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy2.png"));
      break;
    case ES_SKIN3:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy3.png"));
      break;
    case ES_SKIN4:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy4.png"));
      break;
    case ES_SKIN5:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy5.png"));
      break;
    case ES_SKIN6:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy6.png"));
      break;
    case ES_SKIN7:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy7.png"));
      break;
    case ES_SKIN8:
      s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy8.png"));
      break;
    }
}
