#include <app.h>

void App::drawResume()
{
  window.clear();
  window.draw(s_credits_background);
  window.draw(texts.getText("btn_resume"));
  window.draw(texts.getText("btn_menu"));
  window.draw(texts.getText("tip_text"));
  window.draw(texts.getText("tip"));
  window.display();
}
