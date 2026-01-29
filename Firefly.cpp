#include "Effect.h"
#include <FastLED.h>

class Firefly : public Effect {
public:
    Firefly() : leds(nullptr), numLeds(0), fireflies(nullptr), lastMillis(0) {}
    ~Firefly() { delete[] fireflies; }

    void begin(CRGB* ledsArray, int num_leds) override {
        leds = ledsArray;
        numLeds = num_leds;
        lastMillis = millis();

        delete[] fireflies;
        fireflies = new FireflyData[numLeds];

        // init fireflies
        for (int i = 0; i < numLeds; i++) {
            fireflies[i].brightness = 0;
            fireflies[i].color = colors[random(sizeof(colors)/sizeof(colors[0]))];
        }
    }

    void update(uint16_t value) override {
        if (!leds || !fireflies) return;

        unsigned long now = millis();
        uint16_t speed = map(value, 0, 1023, 20, 100); // blink speed
        if (now - lastMillis < speed) return;
        lastMillis = now;

        for (int i = 0; i < numLeds; i++) {
            // light up new firefly
            if (fireflies[i].brightness == 0 && random(100) < 15) {
                fireflies[i].brightness = 50 + random(206);
                fireflies[i].color = colors[random(sizeof(colors)/sizeof(colors[0]))];
            }

            leds[i] = fireflies[i].color;
            leds[i].nscale8(fireflies[i].brightness);

            // fade out
            if (fireflies[i].brightness > fadeAmount) {
                fireflies[i].brightness -= fadeAmount;
            } else {
                fireflies[i].brightness = 0;
            }
        }
    }

private:
    CRGB* leds;
    int numLeds;
    unsigned long lastMillis;

    struct FireflyData {
        CRGB color;
        uint8_t brightness;
    };

    FireflyData* fireflies;

    static const int fadeAmount = 15;      // fade speed
    CRGB colors[7] = {
        CRGB(0, 0, 0),         // black
        CRGB(0, 100, 255),     // blue
        CRGB(255, 50, 200),    // neon pink
        CRGB(255, 150, 50),    // beige-orange
        CRGB(150, 50, 255),    // purple
        CRGB(50, 255, 200),    // turquoise
        CRGB(255, 50, 150)     // magenta
    };
};
