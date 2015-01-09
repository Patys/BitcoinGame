#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ShakingText : public sf::Drawable
{
 public:
  ShakingText();
  ShakingText(const std::string& string, sf::Font& font, int character_size = 32);

  sf::Text& text() { return this->m_text; }

  void shake(float delta_time);

  void setShaking(bool _is_shaking) { is_shaking = _is_shaking; }
  const bool isShaking() const { return this->is_shaking; }
  
  void setSpeed(float _speed) { speed = _speed; }
  const float getSpeed() const { return this->speed; }

  void setFrequency(float _frequency) { frequency = _frequency; }
  const float getFrequency() const { return this->frequency; }

  const sf::Vector2f getSizeOfText() const { return sf::Vector2f(m_text.getLocalBounds().width, m_text.getLocalBounds().height); }
  const sf::Vector2f getCenterOfText() const { return sf::Vector2f(getSizeOfText().x / 2, getSizeOfText().y / 2); }

  void show() { visible = true; }
  void hide() { visible = false; }
  void setVisible(bool visible) { this->visible = visible; }
  const bool isVisible() const { return this->visible; }
  
  //void draw(sf::RenderWindow& window) const;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  sf::Text m_text;

  bool is_shaking;
  float speed;
  float frequency;
  
  float timer;
  int direction;
  bool visible;
};

class TextManager
{
 public:
  TextManager();

  void update(float delta_time);

  bool addText(const std::string& text_id);
  bool addText(const std::string& text_id, ShakingText& text);
  bool deleteText(const std::string& text_id);

  ShakingText& getText(const std::string& text_id);
 
  const int size() { return texts.size(); }

 private:
  std::map<std::string, ShakingText> texts;

};
