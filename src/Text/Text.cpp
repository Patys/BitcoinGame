#include <Text.h>
#include <iostream>

ShakingText::ShakingText():
  m_text(),
  is_shaking(0),
  speed(50),
  frequency(0.2),
  timer(0),
  direction(1),
  visible(true)
{

}

ShakingText::ShakingText(const std::string& string, sf::Font& font, int character_size):
  m_text(),
  is_shaking(0),
  speed(50),
  frequency(0.2),
  timer(0),
  direction(1),
  visible(true)
{
  m_text.setFont(font);
  m_text.setString(string);
  m_text.setCharacterSize(character_size);
}

void ShakingText::shake(float delta_time)
{
  timer += delta_time;
  if(isShaking())
    {
      if(timer > getFrequency())
	{
 	  direction = -direction;
	  m_text.setRotation(0);
	  timer = 0;
	}
      float angel = getSpeed() * delta_time * direction;
      m_text.rotate(angel);
    }
}

void ShakingText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(isVisible())
    {
      target.draw(m_text, states);
    }
}


TextManager::TextManager():
  texts()
{

}

void TextManager::update(float delta_time)
{
  for( auto it = texts.begin(); it != texts.end(); ++it)
    {
      it->second.shake(delta_time);
    }
}

bool TextManager::addText(const std::string& text_id)
{
  texts[text_id] = ShakingText();
  return true;
}

bool TextManager::addText(const std::string& text_id, ShakingText& text)
{
  texts[text_id] = text;
  return true;
}

bool TextManager::deleteText(const std::string& text_id)
{
  if(texts.empty() == false)
    {
      auto it = texts.find(text_id);
      texts.erase(it);
      return true;
    }
  else
    return false;
}

ShakingText& TextManager::getText(const std::string& text_id)
{
  return texts.find(text_id)->second;
}
