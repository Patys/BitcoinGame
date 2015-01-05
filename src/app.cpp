#include <app.h>

App::App():
  window(sf::VideoMode(800, 600), "BTC", sf::Style::Close),
  small_explosion_sprite(sf::milliseconds(50), true, false),
  bonus_animation_sprite(sf::milliseconds(50), true, false),
  player(),
  txt_manager()
{
  srand(time(0));
  window.setFramerateLimit(60);

  s_btc.setTexture(tex_menager.getTexture("data/graphics/bitcoin32.png"));
  s_enemy.setTexture(tex_menager.getTexture("data/graphics/shuriken.png"));
  s_wallet.setTexture(tex_menager.getTexture("data/graphics/wallet.png"));
  s_bonus.setTexture(tex_menager.getTexture("data/graphics/bonus.png"));
  s_menu_background.setTexture(tex_menager.getTexture("data/graphics/btc_background.png"));
  s_game_background.setTexture(tex_menager.getTexture("data/graphics/btc_game_background.png"));
  s_credits_background.setTexture(tex_menager.getTexture("data/graphics/btc_credits.png"));

  // TEST : lighting - darkness bonus
  s_light.setTexture(tex_menager.getTexture("data/graphics/light.png"));
  tex_lighting.create( 800, 600 );
  // 

  font.loadFromFile("data/RussoOne-Regular.ttf");
  font1.loadFromFile("data/Raleway-Regular.otf");

  b_start.setFont(font);
  b_start.setString("Start");
  b_credits.setFont(font);
  b_credits.setString("Credits");
  b_exit.setFont(font);
  b_exit.setString("Exit");
  b_back.setFont(font);
  b_back.setString("Go to menu.");
  b_menu.setFont(font);
  b_menu.setString("Menu");
  b_resume.setFont(font);
  b_resume.setString("Resume");

  b_back.setPosition(sf::Vector2f(500,500));
  b_start.setPosition(sf::Vector2f(100,100));
  b_credits.setPosition(sf::Vector2f(100,150));
  b_exit.setPosition(sf::Vector2f(100,200));
  b_menu.setPosition(sf::Vector2f(100,150));
  b_resume.setPosition(sf::Vector2f(100,100));

  t_credits.setFont(font1);
  t_credits.setString(L"\
Credits:\nPatryk Szczygło\n\nI hope it helps to promote\nBitcoins.\n\n\
If you can, tell about\nBitcoins to sombody.\
");
  t_credits.setPosition(sf::Vector2f(50,100));
  t_score.setFont(font);

  t_btc_falling.setFont(font);
  t_btc_falling.setCharacterSize(56);
  t_btc_falling.setString("! BITCOINS !");
  t_btc_falling.setPosition(sf::Vector2f(400,300));
  sf::Vector2f center_t_btc_falling(t_btc_falling.getLocalBounds().width/2,
				    t_btc_falling.getLocalBounds().height/2);
  t_btc_falling.setOrigin(center_t_btc_falling);

  t_enemy_falling.setFont(font);
  t_enemy_falling.setCharacterSize(56);
  t_enemy_falling.setString("! SHURIKENS !");
  t_enemy_falling.setPosition(sf::Vector2f(400,300));
  sf::Vector2f center_t_enemy_falling(t_enemy_falling.getLocalBounds().width/2,
				      t_enemy_falling.getLocalBounds().height/2);
  t_enemy_falling.setOrigin(center_t_enemy_falling);

  t_explosion.setFont(font);
  t_explosion.setCharacterSize(56);
  t_explosion.setString("! EXPLOSION !");
  t_explosion.setPosition(sf::Vector2f(400,300));
  sf::Vector2f center_t_explosion(t_explosion.getLocalBounds().width/2,
				  t_explosion.getLocalBounds().height/2);
  t_explosion.setOrigin(center_t_explosion);

  t_keys.setFont(font);
  t_keys.setCharacterSize(56);
  t_keys.setString("! INVERTED KEYS !");
  t_keys.setPosition(sf::Vector2f(400,300));
  sf::Vector2f center_t_keys(t_keys.getLocalBounds().width/2,
				  t_keys.getLocalBounds().height/2);
  t_keys.setOrigin(center_t_keys);

  t_darkness.setFont(font);
  t_darkness.setCharacterSize(56);
  t_darkness.setString("DARKNESS");
  t_darkness.setPosition(sf::Vector2f(400,300));
  sf::Vector2f center_t_darkness(t_darkness.getLocalBounds().width/2,
				 t_darkness.getLocalBounds().height/2);
  t_darkness.setOrigin(center_t_darkness);

  show_t_btc_falling = false;
  show_t_enemy_falling = false;
  show_t_explosion = false;
  show_t_keys = false;
  show_t_darkness = false;

  menu_music.openFromFile("data/audio/rock_theme.wav");
  menu_music.setVolume(80);
  menu_music.setLoop(true);
  game_music.openFromFile("data/audio/loop3.wav");
  game_music.setVolume(80);
  game_music.setLoop(true);
  score_music.openFromFile("data/audio/awesomeness.wav");
  score_music.setVolume(80);
  score_music.setLoop(true);

  btc_soundbuffer.loadFromFile("data/audio/handleCoins.ogg");
  btc_sound.setBuffer(btc_soundbuffer);
  enemy_soundbuffer.loadFromFile("data/audio/handleCoins.ogg");
  enemy_sound.setBuffer(enemy_soundbuffer);
  explosion_soundbuffer.loadFromFile("data/audio/explosion.wav");
  explosion_sound.setBuffer(explosion_soundbuffer);
  alarm_soundbuffer.loadFromFile("data/audio/alarm_0.ogg");
  alarm_sound.setBuffer(alarm_soundbuffer);

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

  bonus_animation.setSpriteSheet(tex_menager.getTexture("data/graphics/bonus_animation.png"));
  bonus_animation.addFrame(sf::IntRect(0, 0, 55, 55));
  bonus_animation.addFrame(sf::IntRect(55, 0, 55, 55));
  bonus_animation.addFrame(sf::IntRect(110, 0, 55, 55));
  bonus_animation.addFrame(sf::IntRect(165, 0, 55, 55));
  bonus_animation.addFrame(sf::IntRect(220, 0, 55, 55));
  bonus_animation.addFrame(sf::IntRect(275, 0, 55, 55));


  for(int i = 0; i < 25; i++)
    {
      explosion_sprites.push_back(AnimatedSprite(sf::milliseconds(50), true, false));
    }

  state = MENU;
  
  bitcoin_timer = 1000;
  enemy_timer = 1000;
  bonus_timer = 4000;

  difficulty_timer = 1.1;

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
