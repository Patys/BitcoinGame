#pragma once

#include <Skin.h>

enum PLAYERSKINS { 
  PS_BASIC = 1, // basic skin
  PS_FACE = 2, // skin with simple face
  PS_TEST1 = 3,
  PS_TEST2 = 4,
  PS_TEST3 = 5,
  PS_TEST4 = 6,
  PS_TEST5 = 7,
  PS_TEST6 = 8
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
