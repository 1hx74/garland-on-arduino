#include "Effect.h"
#include <FastLED.h>

class Embers : public Effect {
public:
  CRGB* leds;
  int numLeds;

  uint8_t* baseHue;
  uint8_t* phase;

  void begin(CRGB* ledsArr, int n) override {
    leds = ledsArr;
    numLeds = n;

    baseHue = new uint8_t[numLeds];
    phase   = new uint8_t[numLeds];

    for (int i = 0; i < numLeds; i++) {
      baseHue[i] = random8(10, 35);
      phase[i]   = random8();
    }
  }

  void update(uint16_t value) override {
    uint8_t maxBrightness = map(value, 0, 1023, 40, 255);

    for (int i = 0; i < numLeds; i++) {
      
      uint8_t breathe = sin8(phase[i]);
      uint8_t bright = map(breathe, 0, 255, maxBrightness / 3, maxBrightness);

      leds[i] = CHSV(
        baseHue[i],
        180,
        bright
      );

      phase[i] += random8(1, 3);
    }

    if (random8() < 3) {
      int pos = random(numLeds);
      leds[pos] += CRGB(30, 10, 0);
    }
  }
};
