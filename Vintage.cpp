#pragma once
#include "Effect.h"

class Vintage : public Effect {
public:
    Vintage() {}

    ~Vintage() {
        // free dynamic memory
        delete[] currentColors;
        delete[] targetColors;
        delete[] chosen;
    }

    void begin(CRGB* leds, int num_leds) override {
        this->leds = leds;
        this->num_leds = num_leds;

        // allocate exactly for real number of leds
        if (!bAlloc) {
            currentColors = new CRGB[num_leds];
            targetColors  = new CRGB[num_leds];
            chosen        = new bool[num_leds];
            bAlloc = true;
        }

        for (int i = 0; i < num_leds; i++) {
            targetColors[i] = CRGB::Black;
            currentColors[i] = CRGB::Black;
            chosen[i] = false;
        }

        relayInterval = chooseRelayInterval();
        lastRelayTime = millis() - relayInterval;
    }

    void update(uint16_t value) override {
        unsigned long now = millis();

        if (now - lastRelayTime > relayInterval) {
            lastRelayTime = now;
            relayInterval = chooseRelayInterval(); // change interval

            // count lamp to ON
            int maxOn = max(1, num_leds * 60 / 100); // max 60%
            int minUsual = num_leds * 27 / 100;
            int maxUsual = num_leds * 38 / 100;

            int numOn;
            if (random(100) < 10) {
                // rarely - 2-5 lamp
                numOn = min(random(2, 5), num_leds);
            } else {
                // more often — 27-38%
                numOn = random(minUsual, maxUsual + 1);
            }

            // mask
            for (int i = 0; i < num_leds; i++) {
                chosen[i] = false;
            }

            int count = 0;

            // 1) which are not extinguished
            for (int i = 0; i < num_leds; i++) {
                if (currentColors[i] != CRGB::Black && random(100) < 17) {
                    chosen[i] = true;
                    count++;
                }
            }

            // 2) add new
            while (count < numOn) {
                int i = random(0, num_leds);
                if (chosen[i]) continue;

                // avoid same color clusters
                int colorIndex;
                for (int tries = 0; ; tries++) {
                    colorIndex = chooseColorIndex();
                    if (!sameNeighborColor(i, colorIndex) || tries >= 2) break;
                }

                int level = chooseLevel();
                float brightnessFactor = brightnessLevel(level);

                targetColors[i] = color[colorIndex];
                targetColors[i].r = color[colorIndex].r * brightnessFactor;
                targetColors[i].g = color[colorIndex].g * brightnessFactor;
                targetColors[i].b = color[colorIndex].b * brightnessFactor;

                chosen[i] = true;
                count++;
            }

            // 3) black
            for (int i = 0; i < num_leds; i++) {
                if (!chosen[i]) {
                    targetColors[i] = CRGB::Black;
                }
            }
        }

        // update
        for (int i = 0; i < num_leds; i++) {
            currentColors[i].r = lampFade(currentColors[i].r, targetColors[i].r);
            currentColors[i].g = lampFade(currentColors[i].g, targetColors[i].g);
            currentColors[i].b = lampFade(currentColors[i].b, targetColors[i].b);
            leds[i] = currentColors[i];
        }
    }

private:
    CRGB* leds;
    int num_leds;

    CRGB* currentColors;
    CRGB* targetColors;
    bool* chosen;

    bool bAlloc = false;

    unsigned long lastRelayTime;
    unsigned long relayInterval;

    CRGB color[4] = {
        CRGB(255, 60, 10),   // amber
        CRGB(40, 160, 60),   // lamp green
        CRGB(25, 50, 180),   // muted blue
        CRGB(255, 10, 5)     // red
    };

    // tube smooth extinguishing
    uint8_t lampFade(uint8_t current, uint8_t target) {
        if (current < target) {
            int val = current + max(1, (target - current) / 2);
            if (val > target) val = target;
            return val;
        } else if (current > target) {
            float power = 1.78;
            float k = 0.02 + ((float)random(0, 10) / 1000.0);
            float val = current - pow(current, power) * k;
            val += random(-2, 3);
            if (val < target) val = target;
            if (val > 255) val = 255;
            return (uint8_t)val;
        }
        return current;
    }

    // gamma-cor.
    float brightnessLevel(int level) {
        float gamma = 2.2;
        float norm = (level + 1) / 3.0;
        return pow(norm, 1.0 / gamma);
    }

    // br.
    int chooseLevel() {
        int r = random(100);
        if (r < 20) return 0;        // min
        else if (r < 50) return 1;   // med
        else return 2;               // max
    }

    const int relayTimes[7] = {500, 750, 1000, 1250, 1500, 1750, 2000};
    const int relayWeights[7] = {1, 3, 5, 5, 5, 3, 1};
    const int relayWeightSum = 23;

    int chooseRelayInterval() {
        int r = random(relayWeightSum);
        int sum = 0;
        for (int i = 0; i < 7; i++) {
            sum += relayWeights[i];
            if (r < sum) return relayTimes[i];
        }
        return relayTimes[3];
    }

    // color distribution
    const int colorWeights[4] = {
        6,  // amber
        5,  // green
        2,  // blue
        4   // red
    };
    const int colorWeightSum = 17;

    int chooseColorIndex() {
        int r = random(colorWeightSum);
        int sum = 0;
        for (int i = 0; i < 4; i++) {
            sum += colorWeights[i];
            if (r < sum) return i;
        }
        return 0;
    }

    // neighbor color check
    bool sameNeighborColor(int index, int colorIndex) {
        if (index > 0 && chosen[index - 1]) {
            if (targetColors[index - 1] == color[colorIndex]) return true;
        }
        if (index < num_leds - 1 && chosen[index + 1]) {
            if (targetColors[index + 1] == color[colorIndex]) return true;
        }
        return false;
    }
};
