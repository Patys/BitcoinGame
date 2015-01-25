#pragma once

#include <Skin.h>

enum ENEMYSKINS { 
  ES_STONE = 1, // basic skin
  ES_SHURIKEN = 2 
};

class EnemySkin : public Skin
{
 public:
 EnemySkin():type(ES_STONE) {}

  void setType(ENEMYSKINS type) { this->type = type; }
  ENEMYSKINS getType() { return this->type; }

 private:
  ENEMYSKINS type;
};
