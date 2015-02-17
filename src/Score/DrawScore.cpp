#include <app.h>

void App::drawScore()
{
  window.clear();
  window.draw(s_credits_background);
  window.draw(texts.getText("score"));
  window.draw(texts.getText("game_score"));
  window.draw(texts.getText("btn_back"));
  window.draw(texts.getText("btn_restart"));
  window.draw(texts.getText("tip_text"));
  window.draw(texts.getText("tip"));
  window.display();
}
