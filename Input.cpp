#include "Input.h"

Input::Input(InputState* outState, int buttonPin, int knobPin, int lightPin)
  : outState(outState),
    buttonPin(buttonPin),
    knobPin(knobPin),
    lightPin(lightPin),
    btnState(IDLE),
    pressStartTime(0),
    lastClickTime(0),
    clickCount(0),
    filteredKnob(0),
    filteredLight(0)
{
}

void Input::begin() {
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(knobPin, INPUT);
    pinMode(lightPin, INPUT);

    state = {};
    filteredKnob = analogRead(knobPin);
    filteredLight = analogRead(lightPin);
}

void Input::update() {
    state.buttonClick = false;
    state.buttonDoubleClick = false;
    state.buttonLongPress = false;
    state.buttonLongLongPress = false;
    state.buttonPressed = false;

    bool current = (digitalRead(buttonPin) == LOW);
    unsigned long now = millis();

    switch (btnState) {
        case IDLE:
            if (current) {
                btnState = PRESS;
                pressStartTime = now;
            } else if (clickCount > 0 && (now - lastClickTime) >= DOUBLECLICK_MS) {
                if (clickCount == 1) state.buttonClick = true;
                else if (clickCount >= 2) state.buttonDoubleClick = true;
                clickCount = 0;
            }
            break;

        case PRESS:
            if (!current) {
                if ((now - pressStartTime) < LONGPRESS_MS) {
                    clickCount++;
                    lastClickTime = now;
                }
                btnState = IDLE;
            } else if ((now - pressStartTime) >= LONGPRESS_MS) {
                btnState = LONG;
                state.buttonLongPress = true;
            }
            break;

        case LONG:
            if (!current) {
                btnState = IDLE;
            } else if ((now - pressStartTime) >= LONGLONGPRESS_MS) {
                btnState = LONGLONG;
                state.buttonLongLongPress = true;
            }
            break;

        case LONGLONG:
            if (!current) {
                btnState = IDLE;
            }
            break;
    }

    state.buttonPressed = current;

    // analog + filter
    int rawKnob = analogRead(knobPin);
    filteredKnob = FILTER_ALPHA * rawKnob + (1 - FILTER_ALPHA) * filteredKnob;
    state.knobAngle = (uint16_t)filteredKnob;

    int rawLight = analogRead(lightPin);
    filteredLight = FILTER_ALPHA * rawLight + (1 - FILTER_ALPHA) * filteredLight;
    state.lightSensor = (uint16_t)filteredLight;

    *outState = state;
}
