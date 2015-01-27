#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <random>

#include <ResourceMenager.h>
#include <animated_sprite.h>

#include <player.h>
#include <enemy.h>
#include <bitcoin.h>
#include <bonus.h>
#include <Text.h>
#include <SettingSkins.h>

enum APP_STATE {MENU, GAME, CREDITS, SCORE, RESUME, SHOP};

// generator random numbers
extern std::default_random_engine number_generator;

class App;

class Shop 
{
 public:
  Shop();

  void init(App* app);

  void update(App* app);
  void draw(App* app);

 private:
  void createPlayerSkin(App* app, const std::string& id,
			const std::string& name, const std::string& des, PLAYERSKINS type);
  void createEnemySkin(App* app, const std::string& id,
		       const std::string& name, const std::string& des, ENEMYSKINS type);

  std::vector<Skin*> skins;
  TextManager texts;
  sf::RectangleShape select_rectangle;

  PLAYERSKINS select_player_skin;
  ENEMYSKINS select_enemy_skin;

};


class App
{
 public:
  App();

  void run();
  // //

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
  void addSpeedEnemy();

  void checkSettings();

  bool immortalityIsEnding();

  void setGameScore(int value) { this->game_score = value; }

  sf::RenderWindow window;
  sf::Event event;

  std::vector<Bitcoin> bitcoins;
  std::vector<EndGameBitcoin> end_game_bitcoins;
  std::vector<Enemy> enemies;
  std::vector<Bonus> bonuses;
  std::vector<ActiveBonus> active_bonuses;
  std::vector<GameObject> baloons;
  Player player;
  
  // player things: - buying in shop
  int game_score;
  SettingSkins setting_skins;
  Shop shop;

  // state - 1-game, 2-menu, 3-credits, 4-score
  APP_STATE state;
  
  sf::Clock bitcoin_clock;
  sf::Clock enemy_clock;
  sf::Clock bonus_clock;

  float bitcoin_timer;
  float enemy_timer;
  float bonus_timer;

  float difficulty_timer;

  sf::Vector2f speed_enemy_position;
  bool speed_enemy;

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
  sf::Sprite s_bloody_btc;
  sf::Sprite s_enemy;
  sf::Sprite s_wallet;
  sf::Sprite s_wallet_dead;
  sf::Sprite s_bonus;
  sf::Sprite s_explosion;
  sf::Sprite s_bonus_immortality;
  sf::Sprite s_baloon;
  sf::Sprite s_warning;

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
