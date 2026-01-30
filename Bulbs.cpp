#include "Effect.h"
#include <FastLED.h>

class Bulbs : public Effect {
public:
    Bulbs() : leds(nullptr), numLeds(0), lastMillis(0), state(false) {}

    void begin(CRGB* ledsArray, int num_leds) override {
        leds = ledsArray;
        numLeds = num_leds;
        lastMillis = millis();
        state = false;
    }

    void update(uint16_t value) override {
        if (!leds) return;

        unsigned long now = millis();
        uint16_t speed = map(value, 0, 1023, 100, 2000); // speed

        if (now - lastMillis < speed) return;
        lastMillis = now;

        state = !state;

        CRGB red    = CRGB(255, 0, 0);
        CRGB orange = CRGB(255, 120, 0);

        for (int i = 0; i < numLeds; i++) {
            bool even = (i % 2 == 0);

            if (state) {
                leds[i] = even ? orange : red;
            } else {
                leds[i] = even ? red : orange;
            }
        }
    }

private:
    CRGB* leds;
    int numLeds;
    unsigned long lastMillis;
    bool state;
};
