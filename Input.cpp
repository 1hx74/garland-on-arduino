#include "Input.h"

Input::Input(int buttonPin, int knobPin, int lightPin)
  : buttonPin(buttonPin),
    knobPin(knobPin),
    lightPin(lightPin),
    lastButtonState(false),
    lastPressTime(0),
    lastClickTime(0),
    clickCount(0)
{
}

void Input::begin() {
  state = {};
}

void Input::update() {
    state.buttonClick = false;
    state.buttonDoubleClick = false;
    state.buttonLongPress = false;

    bool current = (digitalRead(buttonPin) == LOW);
    unsigned long now = millis();

    // click
    if (current && !lastButtonState) {
        lastPressTime = now;
    }

    // long click
    if (current && !state.buttonLongPress && (now - lastPressTime) >= LONGPRESS_MS) {
        state.buttonLongPress = true;
        clickCount = 0; // отменяем клики
    }

    // unclick
    if (!current && lastButtonState) {
        if ((now - lastPressTime) < LONGPRESS_MS) {
            clickCount++;
            lastClickTime = now;
        }
    }

    // processed click
    if (clickCount > 0) {
        if ((now - lastClickTime) >= DOUBLECLICK_MS) {
            if (clickCount == 1) state.buttonClick = true;
            else state.buttonDoubleClick = true;
            clickCount = 0;
        }
    }

    lastButtonState = current;
    state.buttonPressed = current;

    // analog sensors
    static float filteredKnob = analogRead(knobPin);
    static float filteredLight = analogRead(lightPin);

    int rawKnob = analogRead(knobPin);
    filteredKnob = 0.1f * rawKnob + 0.9f * filteredKnob;
    state.knobAngle = (uint16_t)filteredKnob;

    int rawLight = analogRead(lightPin);
    filteredLight = 0.1f * rawLight + 0.9f * filteredLight;
    state.lightSensor = (uint16_t)filteredLight;
}

const InputState& Input::getState() const {
  return state;
}
