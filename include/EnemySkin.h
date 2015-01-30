#pragma once

#include <Skin.h>

enum ENEMYSKINS { 
  ES_SKIN1 = 1, // basic skin
  ES_SKIN2 = 2,
  ES_SKIN3 = 3,
  ES_SKIN4,
  ES_SKIN5,
  ES_SKIN6,
  ES_SKIN7,
  ES_SKIN8
};

class EnemySkin : public Skin
{
 public:
 EnemySkin():type(ES_SKIN1) {}

  void setType(ENEMYSKINS type) { this->type = type; }
  ENEMYSKINS getType() { return this->type; }

 private:
  ENEMYSKINS type;
};
