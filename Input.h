#pragma once
#include <Arduino.h>
#include "InputState.h"

#define LONGPRESS_MS       1000
#define LONGLONGPRESS_MS   3000
#define DOUBLECLICK_MS     400
#define FILTER_ALPHA       0.4f

enum ButtonState {
    IDLE,
    PRESS,
    LONG,
    LONGLONG,
    RELEASE,
    CLICK_CHECK
};

class Input {
public:
    Input(int buttonPin, int knobPin, int lightPin);
    void begin();
    void update();
    const InputState& getState() const;

private:
    int buttonPin;
    int knobPin;
    int lightPin;

    InputState state;

    ButtonState btnState;
    unsigned long pressStartTime;
    unsigned long lastClickTime;
    int clickCount;

    float filteredKnob;
    float filteredLight;
};