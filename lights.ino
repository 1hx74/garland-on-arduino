#define P_BUTTON 8
#define P_KNOB   A0
#define P_LIGHT  A5 

#include <Arduino.h>
#include "Input.h"

Input input(P_BUTTON, P_KNOB, P_LIGHT);
InputState nowState;

void setup() {
  pinMode(P_BUTTON, INPUT_PULLUP);
  pinMode(P_KNOB, INPUT);
  pinMode(P_LIGHT, INPUT);

  input.begin();
}

void loop() {
  input.update();
  nowState = input.getState();

  unsigned long currentMillis = millis();

  // click processing
  if (nowState.buttonClick) {

  }
  if (nowState.buttonDoubleClick) {

  }
  if (nowState.buttonLongPress) {

  }

  uint16_t knobValue = nowState.knobAngle;
}
