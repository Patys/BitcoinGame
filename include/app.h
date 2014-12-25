#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include <ResourceMenager.h>
#include <animated_sprite.h>

#include <player.h>
#include <enemy.h>
#include <bitcoin.h>
#include <bonus.h>

enum APP_STATE {MENU, GAME, CREDITS, SCORE};

class App
{
 public:
  App();

  void run();
  // //
 private:

  void draw();
  void update();

  void updateBitcoins(float delta_time);
  void updateEnemies(float delta_time);
  void updatePlayer(float delta_time);
  void updateBonuses();
  void updateActiveBonuses();

  void restart();

  // add after x milliseconds
  void addBitcoin(float milliseconds);
  void addEnemy(float milliseconds);
  void addBonus(float milliseconds);

  sf::RenderWindow window;
  sf::Event event;

  std::vector<Bitcoin> bitcoins;
  std::vector<Enemy> enemies;
  std::vector<Bonus> bonuses;
  std::vector<ActiveBonus> active_bonuses;
  Player player;

  // state - 1-game, 2-menu, 3-credits, 4-score
  APP_STATE state;
  
  sf::Clock bitcoin_clock;
  sf::Clock enemy_clock;
  sf::Clock bonus_clock;
  float bitcoin_timer;
  float enemy_timer;
  float bonus_timer;

  bool show_t_btc_falling;
  bool show_t_enemy_falling;
  bool show_t_explosion;

  Animation explosion;
  std::vector<AnimatedSprite> explosion_sprites;

  Animation small_explosion;
  AnimatedSprite small_explosion_sprite;

  // texture holder
  ResourceMenager tex_menager;
  
  // sf::Font ...
  sf::Font font;
  sf::Font font1;

  // sf::Sprite ...
  sf::Sprite s_btc;
  sf::Sprite s_enemy;
  sf::Sprite s_wallet;
  sf::Sprite s_double_btc_bonus;
  sf::Sprite s_double_enemy_bonus;
  sf::Sprite s_explode_bonus;
  sf::Sprite s_explosion;

  sf::Sprite s_menu_background;
  sf::Sprite s_game_background;
  sf::Sprite s_credits_background;

  // sf::Text ...
  sf::Text b_start;
  sf::Text b_credits;
  sf::Text b_exit;
  sf::Text b_back;
  sf::Text t_credits;
  sf::Text t_score;
  sf::Text t_btc_falling;
  sf::Text t_enemy_falling;
  sf::Text t_explosion;

  // sf::Music ...
  sf::Music menu_music;
  sf::Music game_music;
  sf::Music score_music;

  // sf::Sound ...
  sf::SoundBuffer btc_soundbuffer;
  sf::Sound btc_sound;
  sf::SoundBuffer enemy_soundbuffer;
  sf::Sound enemy_sound;
  sf::SoundBuffer explosion_soundbuffer;
  sf::Sound explosion_sound;
  sf::SoundBuffer alarm_soundbuffer;
  sf::Sound alarm_sound;
};
