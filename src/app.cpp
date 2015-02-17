#include <app.h>

std::default_random_engine number_generator;

App::App():
  window(sf::VideoMode(800, 600), "BTC", sf::Style::Close),
  player(),
  setting_skins(),
  small_explosion_sprite(sf::milliseconds(50), true, false),
  texts(),
  shop_texts(), select_player_skin(PS_SKIN1), select_enemy_skin(ES_SKIN1), 
  shop_state(MAINSHOP)
{
  window.setFramerateLimit(60);

  s_btc.setTexture(tex_menager.getTexture("data/graphics/bitcoin32.png"));
  s_enemy.setTexture(tex_menager.getTexture("data/graphics/enemy1.png"));
  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet1.png"));
  s_wallet_dead.setTexture(tex_menager.getTexture("data/graphics/wallet_dead.png"));
  s_bonus.setTexture(tex_menager.getTexture("data/graphics/bonus.png"));
  s_menu_background.setTexture(tex_menager.getTexture("data/graphics/btc_background.png"));
  s_game_background.setTexture(tex_menager.getTexture("data/graphics/background/btc_game_background.png"));
  s_credits_background.setTexture(tex_menager.getTexture("data/graphics/btc_credits.png"));
  s_baloon.setTexture(tex_menager.getTexture("data/graphics/baloon.png"));
  s_bloody_btc.setTexture(tex_menager.getTexture("data/graphics/bloody_btc.png"));
  s_bonus_immortality.setTexture(tex_menager.getTexture("data/graphics/immortality.png"));
  s_warning.setTexture(tex_menager.getTexture("data/graphics/warning.png"));

  // lighting - darkness bonus
  s_light.setTexture(tex_menager.getTexture("data/graphics/light.png"));
  tex_lighting.create( 800, 600 );
  //

  font.loadFromFile("data/RussoOne-Regular.ttf");
  font1.loadFromFile("data/Raleway-Regular.otf");

  menu_music.openFromFile("data/audio/rock_theme.wav");
  menu_music.setVolume(40);
  menu_music.setLoop(true);
  game_music.openFromFile("data/audio/loop3.wav");
  game_music.setVolume(40);
  game_music.setLoop(true);
  score_music.openFromFile("data/audio/awesomeness.wav");
  score_music.setVolume(40);
  score_music.setLoop(true);

  btc_soundbuffer.loadFromFile("data/audio/handleCoins.ogg");
  btc_sound.setBuffer(btc_soundbuffer);
  btc_sound.setVolume(60);
  enemy_soundbuffer.loadFromFile("data/audio/handleCoins.ogg");
  enemy_sound.setBuffer(enemy_soundbuffer);
  enemy_sound.setVolume(60);
  explosion_soundbuffer.loadFromFile("data/audio/explosion.wav");
  explosion_sound.setBuffer(explosion_soundbuffer);
  explosion_sound.setVolume(60);
  alarm_soundbuffer.loadFromFile("data/audio/alarm_0.ogg");
  alarm_sound.setBuffer(alarm_soundbuffer);
  alarm_sound.setVolume(60);

  explosion.setSpriteSheet(tex_menager.getTexture("data/graphics/explosion3.png"));
  explosion.addFrame(sf::IntRect(1, 1, 89, 89));
  explosion.addFrame(sf::IntRect(93, 1, 89, 89));
  explosion.addFrame(sf::IntRect(185, 1, 89, 89));
  explosion.addFrame(sf::IntRect(277, 1, 89, 89));
  explosion.addFrame(sf::IntRect(369, 1, 89, 89));
  explosion.addFrame(sf::IntRect(1, 93, 89, 89));
  explosion.addFrame(sf::IntRect(93, 93, 89, 89));
  explosion.addFrame(sf::IntRect(185, 93, 89, 89));
  explosion.addFrame(sf::IntRect(277, 93, 89, 89));
  explosion.addFrame(sf::IntRect(369, 93, 89, 89));

  small_explosion.setSpriteSheet(tex_menager.getTexture("data/graphics/explosion3.png"));
  small_explosion.addFrame(sf::IntRect(1, 305, 47, 47));
  small_explosion.addFrame(sf::IntRect(51, 305, 47, 47));
  small_explosion.addFrame(sf::IntRect(101, 305, 47, 47));
  small_explosion.addFrame(sf::IntRect(151, 305, 47, 47));
  small_explosion.addFrame(sf::IntRect(201, 305, 47, 47));
  small_explosion.addFrame(sf::IntRect(251, 305, 47, 47));

  for(int i = 0; i < 25; i++)
    {
      explosion_sprites.push_back(AnimatedSprite(sf::milliseconds(50), true, false));
    }
  for(int i = 0; i < 10; i++)
    {
      end_game_bitcoins.push_back(EndGameBitcoin());
    }

  state = MENU;

  bitcoin_timer = 1000;
  enemy_timer = 1000;
  bonus_timer = 8000;

  difficulty_timer = 1.1;

}

void App::run()
{
  initTexts();

  // TODO: fuck off this shit
  menu_music.play();
  while(window.isOpen())
    {
      update();
      draw();
    }
}
