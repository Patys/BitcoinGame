#include <Text.h>
#include <iostream>

Text::Text():
  is_shaking(0),
  speed(0),
  frequency(1),
  timer(0),
  direction(1)
{

}

void Text::shake(float delta_time)
{
  timer += delta_time;
  if(isShaking())
    {
      if(timer > getFrequency())
	{
	  direction = -direction;
	  setRotation(0);
	  timer = 0;
	}
      float angel = getSpeed() * delta_time * direction;
      rotate(angel);
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
  texts[text_id] = Text();
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

Text& TextManager::getText(const std::string& text_id)
{
  return texts.find(text_id)->second;
}
