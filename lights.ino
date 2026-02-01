#include <Arduino.h>
#include <FastLED.h>
#include "Input.h"
#include "EffectSequence.h"
#include "FSM.h"

#define DAY_BRIGHTNESS    190
#define NIGHT_BRIGHTNESS  100

#define P_BUTTON 8
#define P_KNOB   A0
#define P_LIGHT  A5 

#define NUM_LEDS 50
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

Input input(P_BUTTON, P_KNOB, P_LIGHT);
InputState nowState;

EffectSequence effectSequence;
Effect* nowEffect = nullptr;

FSM fsm(effectSequence, nowEffect, leds, NUM_LEDS);

void setup() {
  input.begin();

  nowEffect = effectSequence.current();
  nowEffect->begin(leds, NUM_LEDS);

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(DAY_BRIGHTNESS);
}


void loop() {
  input.update();
  nowState = input.getState();

  fsm.update(nowState);
  
  FastLED.show();
}
