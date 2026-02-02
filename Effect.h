#pragma once
#include <Arduino.h>
#include <FastLED.h>

/*
  to write an effect, inherit from this class,
  leds is an array of LEDs that will be rendered on the device.
  num_leds - the number of leds.
  Value - the values of the potentiometer at the moment
  (you can use it to control speed or color)
*/

class Effect {
public:

  virtual ~Effect() {}
  virtual void begin(CRGB* leds, int num_leds) {}      // for start effect
  virtual void update(uint16_t value) = 0;
};
