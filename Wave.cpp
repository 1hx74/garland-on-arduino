#include "Effect.h"
#include <FastLED.h>

class Wave : public Effect {
public:
    Wave() : leds(nullptr), numLeds(0), offset(0), lastMillis(0) {}

    void begin(CRGB* ledsArray, int num_leds) override {
        leds = ledsArray;
        numLeds = num_leds;
        offset = 0;
        lastMillis = millis();
    }

    void update(uint16_t value) override {
        if (!leds) return;

        unsigned long now = millis();
        if (now - lastMillis < 7) return; // speed
        lastMillis = now;

        offset++;

        uint8_t hue = map(value, 0, 1023, 0, 255); // color

        for (int i = 0; i < numLeds; i++) {
            uint8_t wave = sin8((numLeds - 1 - i) * 16 + offset);

            // blending for black areas
            uint8_t brightness = qsub8(wave, 60);

            // rm low br to rm flickering
            if (brightness < 5) brightness = 0;

            leds[i] = CHSV(hue, 255, brightness);
        }
    }

private:
    CRGB* leds;
    int numLeds;
    uint8_t offset;
    unsigned long lastMillis;
};
