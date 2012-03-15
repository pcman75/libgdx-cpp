#pragma once
#include "Entity.h"

class BossPart : public Entity 
{
public:
  int dieIn;

  BossPart()
  {
    dieIn = 0;
  }

  virtual void setRot (double rot){};
  virtual void outOfBounds(){};
};
