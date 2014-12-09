#include <app.h>

App::App():
  window(sf::VideoMode(800, 600), "BTC")
{
  srand(time(0));
  window.setFramerateLimit(60);

  s_btc.setTexture(tex_menager.getTexture("data/graphics/bitcoin32.png"));
  s_stone.setTexture(tex_menager.getTexture("data/graphics/stone.png"));
  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet.png"));
  s_double_btc_bonus.setTexture(tex_menager.getTexture("data/graphics/double_btc.png"));
  s_double_stones_bonus.setTexture(tex_menager.getTexture("data/graphics/double_stones.png"));
  s_explode_bonus.setTexture(tex_menager.getTexture("data/graphics/explode.png"));

  font.loadFromFile("data/Raleway-Regular.otf");

  b_start.setFont(font);
  b_start.setString("Start");
  b_credits.setFont(font);
  b_credits.setString("Credits");
  b_exit.setFont(font);
  b_exit.setString("Exit");
  b_back.setFont(font);
  b_back.setString("Go to menu.");

  b_start.setPosition(sf::Vector2f(100,100));
  b_credits.setPosition(sf::Vector2f(100,150));
  b_exit.setPosition(sf::Vector2f(100,200));
  
  t_credits.setFont(font);
  t_credits.setString("Game created by Patys.");
  t_score.setFont(font);

  menu_music.openFromFile("data/audio/rock_theme.wav");
  menu_music.setVolume(80);
  menu_music.setLoop(true);
  game_music.openFromFile("data/audio/loop3.wav");
  game_music.setVolume(80);
  game_music.setLoop(true);

  btc_soundbuffer.loadFromFile("data/audio/handleCoins.ogg");
  btc_sound.setBuffer(btc_soundbuffer);
  stone_soundbuffer.loadFromFile("data/audio/handleCoins.ogg");
  stone_sound.setBuffer(stone_soundbuffer);

  state = MENU;
  
  bitcoin_timer = 1000;
  stone_timer = 1000;
  bonus_timer = 1000;
}

void App::run()
{
  menu_music.play();
  while(window.isOpen())
    {
      update();
      draw();
    }
}
