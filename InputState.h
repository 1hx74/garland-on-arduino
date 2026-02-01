#pragma once
#include <Arduino.h>

struct InputState {
  uint16_t lightSensor;
  uint16_t knobAngle;
  
  bool buttonPressed;
  bool buttonClick;
  bool buttonDoubleClick;
  bool buttonLongPress;
  bool buttonLongLongPress;
};