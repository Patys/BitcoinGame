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
#include <Text.h>

enum APP_STATE {MENU, GAME, CREDITS, SCORE, RESUME};

class App
{
 public:
  App();

  void run();
  // //
 private:

  void initTexts();

  void draw();
  void update();

  void updateBitcoins(float delta_time);
  void updateEnemies(float delta_time);
  void updatePlayer(float delta_time);
  void updateBonuses(float delta_time);

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
  std::vector<GameObject> baloons;
  Player player;

  // state - 1-game, 2-menu, 3-credits, 4-score
  APP_STATE state;
  
  sf::Clock bitcoin_clock;
  sf::Clock enemy_clock;
  sf::Clock bonus_clock;

  float bitcoin_timer;
  float enemy_timer;
  float bonus_timer;

  float difficulty_timer;

  Animation explosion;
  std::vector<AnimatedSprite> explosion_sprites;
  Animation small_explosion;
  AnimatedSprite small_explosion_sprite;

  // texture holder
  ResourceMenager tex_menager;
  // texts manager
  TextManager texts;
  
  // TEST : lighting - darkness bonus
  sf::Sprite s_light;
  sf::RenderTexture tex_lighting;
  sf::Sprite s_lighting;

  // sf::Font ...
  sf::Font font;
  sf::Font font1;

  // sf::Sprite ...
  sf::Sprite s_btc;
  sf::Sprite s_enemy;
  sf::Sprite s_wallet;
  sf::Sprite s_bonus;
  sf::Sprite s_explosion;

  sf::Sprite s_baloon;

  sf::Sprite s_menu_background;
  sf::Sprite s_game_background;
  sf::Sprite s_credits_background;

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
