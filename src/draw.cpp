#include <app.h>

void App::draw()
{
  if(state == GAME)
    {
      drawGame();
    }
  else if(state == MENU)
    {
      drawMenu();
    }
  else if(state == SCORE)
    {  
      drawScore();
    }
  else if(state == CREDITS)
    {
      drawCredits();
    }
  else if(state == RESUME)
    {
      drawResume();
    }
  else if(state == SHOP)
    {
      drawShop();
    }
}
