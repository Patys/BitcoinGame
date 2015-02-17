#include <app.h>

void App::drawCredits()
{
  window.clear();
  window.draw(s_credits_background);
  window.draw(texts.getText("txt_credits"));
  window.draw(texts.getText("btn_back"));
  window.display();
}
