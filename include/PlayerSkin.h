#pragma once

#include <Skin.h>

enum PLAYERSKINS { 
  PS_SKIN1 = 1, // basic skin
  PS_SKIN2 = 2, // skin with simple face
  PS_SKIN3 = 3,
  PS_SKIN4 = 4,
  PS_SKIN5 = 5,
  PS_SKIN6 = 6,
  PS_SKIN7 = 7,
  PS_SKIN8 = 8
};

class PlayerSkin : public Skin
{
 public:
 PlayerSkin():type(PS_SKIN1) {}

  void setType(PLAYERSKINS type) { this->type = type; }
  PLAYERSKINS getType() { return this->type; }

 private:
  PLAYERSKINS type;
};
