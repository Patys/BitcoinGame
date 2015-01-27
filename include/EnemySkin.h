#pragma once

#include <Skin.h>

enum ENEMYSKINS { 
  ES_STONE = 1, // basic skin
  ES_SHURIKEN = 2,
  ES_TEST1 = 3,
  ES_TEST2,
  ES_TEST3,
  ES_TEST4,
  ES_TEST5,
  ES_TEST6
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
