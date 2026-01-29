#pragma once
#include <Arduino.h>
#include <FastLED.h>

class Effect {
public:
  virtual ~Effect() {}
  virtual void begin(CRGB* leds, int num_leds) {}      // for start effect
  virtual void update(uint16_t Value) = 0;
};
