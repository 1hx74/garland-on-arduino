#pragma once
#include <Arduino.h>
#include "Input.h"
#include "EffectSequence.h"

enum class FSMState {
    LOAD,
    AUTO,
    MANUAL,
    DEMO
};

class FSM {
public:
    FSM(EffectSequence& seq, Effect*& currentEffect, CRGB* leds, uint16_t numLeds);

    void update(InputState& state);
    FSMState getState() const;
    void setState(FSMState newState);

private:
    FSMState fsmState;

    EffectSequence& effectSequence;
    Effect*& nowEffect;
    CRGB* leds;
    uint16_t numLeds;
};
