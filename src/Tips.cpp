#include <app.h>


std::vector<std::string> tips = {
  {"Avoid shurikens."},
  {"Take every bitcoin!"},
  {"Bonuses contain good and bad things."},
  {"Check out bitcoin.org"},
  {"Tell to friends about this game."},
  {"Go to bitcoin-patys.rhcloud.com and give me some feedback!"},
  {"Enjoy the game :D"},
  {"Go to shop and buy new skins."},
  {"Send me some feedback."}
};

void App::setRandomTip(ShakingText& text)
{
  std::uniform_int_distribution<int> distribution(0,tips.size()-1);
  int i = distribution(number_generator);
  text.text().setString(tips[i]);
  text.text().setOrigin(text.getCenterOfText());
}
