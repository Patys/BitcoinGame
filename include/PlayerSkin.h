#pragma once

#include <Skin.h>

enum PLAYERSKINS { 
  PS_BASIC = 1, // basic skin
  PS_FACE = 2 // skin with simple face
};

class PlayerSkin : public Skin
{
 public:
 PlayerSkin():type(PS_BASIC) {}

  void setType(PLAYERSKINS type) { this->type = type; }
  PLAYERSKINS getType() { return this->type; }

 private:
  PLAYERSKINS type;
};
