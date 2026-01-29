#pragma once
#include <Arduino.h>
#include "InputState.h"

#define LONGPRESS_MS    1000
#define DOUBLECLICK_MS  400
#define FILTER_ALPHA    0.1f

class Input {
  public:
    Input(int buttonPin, int knobPin, int lightPin);
    //~Input();

    void begin();
    void update();
    const InputState& getState() const;

  private:
    int buttonPin;
    int knobPin;
    int lightPin;

    InputState state;

    bool lastButtonState;
    unsigned long lastPressTime;
    unsigned long lastClickTime;
    int clickCount;
};
