#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include <ResourceMenager.h>

#include <player.h>
#include <stone.h>
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

  void updateBitcoins();
  void updateStones();
  void updatePlayer();
  void updateBonuses();
  void updateActiveBonuses();

  // add after x milliseconds
  void addBitcoin(float milliseconds);
  void addStone(float milliseconds);
  void addBonus(float milliseconds);

  sf::RenderWindow window;
  sf::Event event;
  
  std::vector<Bitcoin> bitcoins;
  std::vector<Stone> stones;
  std::vector<Bonus> bonuses;
  std::vector<ActiveBonus> active_bonuses;
  Player player;

  // state - 1-game, 2-menu, 3-credits, 4-score
  APP_STATE state;
  
  sf::Clock bitcoin_clock;
  sf::Clock stone_clock;
  sf::Clock bonus_clock;
  float bitcoin_timer;
  float stone_timer;
  float bonus_timer;

  // texture holder
  ResourceMenager tex_menager;
  
  // sf::Font ...
  sf::Font font;

  // sf::Sprite ...
  sf::Sprite s_btc;
  sf::Sprite s_stone;
  sf::Sprite s_wallet;
  sf::Sprite s_double_btc_bonus;
  sf::Sprite s_double_stones_bonus;
  sf::Sprite s_explode_bonus;

  // sf::Text ...
  sf::Text b_start;
  sf::Text b_credits;
  sf::Text b_exit;
  sf::Text b_back;
  sf::Text t_credits;
  sf::Text t_score;

  // sf::Music ...
  sf::Music menu_music;
  sf::Music game_music;

  // sf::Sound ...
  sf::SoundBuffer btc_soundbuffer;
  sf::Sound btc_sound;
  sf::SoundBuffer stone_soundbuffer;
  sf::Sound stone_sound;
};
