#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Text : public sf::Text
{
 public:
  Text();
  Text(const std::string& string, sf::Font& font, int character_size = 32);

  void shake(float delta_time);

  void setShaking(bool _is_shaking) { is_shaking = _is_shaking; }
  const bool isShaking() { return is_shaking; }
  
  void setSpeed(float _speed) { speed = _speed; }
  const float getSpeed() { return speed; }

  void setFrequency(float _frequency) { frequency = _frequency; }
  const float getFrequency() { return frequency; }

  const sf::Vector2f getSize() { return sf::Vector2f(getLocalBounds().width, getLocalBounds().height); }
  const sf::Vector2f getCenter() { return sf::Vector2f(getSize().x / 2, getSize().y / 2); }

 private:
  bool is_shaking;
  float speed;
  float frequency;

  float timer;
  int direction;
};

class TextManager
{
 public:
  TextManager();

  void update(float delta_time);

  bool addText(const std::string& text_id);
  bool addText(const std::string& text_id, Text& text);
  bool deleteText(const std::string& text_id);

  Text& getText(const std::string& text_id);
 
  const int size() { return texts.size(); }

 private:
  std::map<std::string, Text> texts;

};
