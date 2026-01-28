#pragma once
#include <Arduino.h>
#include "InputState.h"

struct EffectContext {
  uint32_t time;
  bool isInit;     // effect on
  const InputState& input;
};

class Effect {
public:
  virtual ~Effect() {}
  virtual void begin() {}       // for start effect
  virtual void update(const EffectContext& ctx) = 0;
};
