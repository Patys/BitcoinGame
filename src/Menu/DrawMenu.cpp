#include <app.h>

void App::drawMenu()
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
