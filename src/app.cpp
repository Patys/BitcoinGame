#include <app.h>

App::App():
  window(sf::VideoMode(800, 600), "BTC", sf::Style::Close),
  small_explosion_sprite(sf::milliseconds(50), true, false),
  bonus_animation_sprite(sf::milliseconds(50), true, false),
  player(),
  texts()
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

void App::initTexts()
{
  Text btn_start("Start", font);
  btn_start.setPosition(sf::Vector2f(100, 100));
  texts.addText("btn_start", btn_start);

  Text btn_credits("Credits", font);
  btn_credits.setPosition(sf::Vector2f(100, 150));
  texts.addText("btn_credits", btn_credits);

  Text btn_exit("Exit", font);
  btn_exit.setPosition(sf::Vector2f(100, 200));
  texts.addText("btn_exit", btn_exit);
  
  Text btn_back("Go to menu", font);
  btn_back.setPosition(sf::Vector2f(500,500));
  texts.addText("btn_back", btn_back);

  Text btn_menu("Menu", font);
  btn_menu.setPosition(sf::Vector2f(100,150));
  texts.addText("btn_menu", btn_menu);
  
  Text btn_resume("Resume", font);
  btn_resume.setPosition(sf::Vector2f(100,100));
  texts.addText("btn_resume", btn_resume);

  Text t_credits("", font1);
  t_credits.setString(L"Credits:\nPatryk Szczygło\n\nI hope it helps to promote\nBitcoins.\n\n\
If you can, tell about\nBitcoins to sombody.");
  t_credits.setPosition(sf::Vector2f(50,100));
  texts.addText("txt_credits", t_credits);

  Text t_btc("BITCOINS", font, 56);
  t_btc.setPosition(sf::Vector2f(400,300));
  texts.addText("txt_btc_falling", t_btc);
  texts.getText("txt_btc_falling").setOrigin(texts.getText("txt_btc_falling").getCenter());
  texts.getText("txt_btc_falling").setShaking(true);

  Text t_enemy("SHURIKENS", font, 56);
  t_enemy.setPosition(sf::Vector2f(400,300));
  texts.addText("txt_enemy_falling", t_enemy);
  texts.getText("txt_enemy_falling").setOrigin(texts.getText("txt_enemy_falling").getCenter());
  texts.getText("txt_enemy_falling").setShaking(true);

  Text t_explosion("EXPLOSION", font, 56);
  t_explosion.setPosition(sf::Vector2f(400,300));
  texts.addText("txt_explosion", t_explosion);
  texts.getText("txt_explosion").setOrigin(texts.getText("txt_explosion").getCenter());
  texts.getText("txt_explosion").setShaking(true);

  Text t_keys("INVERTED KEYS", font, 56);
  t_keys.setPosition(sf::Vector2f(400,300));
  texts.addText("txt_inverted_keys", t_keys);
  texts.getText("txt_inverted_keys").setOrigin(texts.getText("txt_inverted_keys").getCenter());
  texts.getText("txt_inverted_keys").setShaking(true);

  Text t_darkness("DARKNESS", font, 56);
  t_darkness.setPosition(sf::Vector2f(400,300));
  texts.addText("txt_darkness", t_darkness);
  texts.getText("txt_darkness").setOrigin(texts.getText("txt_darkness").getCenter());
  texts.getText("txt_darkness").setShaking(true);
  
  Text t_score("", font);
  texts.addText("score", t_score);
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
