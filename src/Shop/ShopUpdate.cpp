#include <app.h>


void App::updateShop()
{
  s_wallet.setRotation(0);
  s_enemy.setRotation(0);

  if(shop_state == MAINSHOP)
    {
      updateMainShop();
    }
  if(shop_state == PLAYERSHOP)
    {
      updatePlayerShop();

    }
  if(shop_state == ENEMYSHOP)
    {
      updateEnemyShop();
    }
}
