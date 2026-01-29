#pragma once
#include "Effect.h"

#define EFFECT_COUNT    0

class EffectSequence {
  public:
    EffectSequence();
    //~EffectSequence();
    Effect* next();
    Effect* prev();
    Effect* current();

  private:
    Effect* sequence[EFFECT_COUNT];
    int idx;
};
