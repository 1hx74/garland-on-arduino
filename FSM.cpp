#include "FSM.h"

FSM::FSM(InputState* state, EffectSequence& effectSequence, Effect*& nowEffect, CRGB* leds, uint16_t NUM_LEDS)
    : fsmState(FSMState::LOAD),
      state(state),
      effectSequence(effectSequence),
      nowEffect(nowEffect),
      leds(leds),
      numLeds(NUM_LEDS)
{}

FSMState FSM::getState() const {
    return fsmState;
}

void FSM::setState(FSMState newState) {
    fsmState = newState;
}

void FSM::update() {
    if (!state) return;

    uint16_t knobValue = state->knobAngle;

    switch (fsmState) {

        case FSMState::LOAD:
            // todo begin anim. and block click
            nowEffect = effectSequence.current();
            nowEffect->begin(leds, numLeds);
            setState(FSMState::MANUAL);
            break;

        case FSMState::AUTO:
            // todo auto
            break;

        case FSMState::MANUAL:
            if (state->buttonClick) {
                nowEffect = effectSequence.next();
                nowEffect->begin(leds, numLeds);
            } 
            else if (state->buttonDoubleClick) {
                nowEffect = effectSequence.prev();
                nowEffect->begin(leds, numLeds);
            } 
            else if (state->buttonLongPress) {
                // todo -> add/rm fav.
            }
            else if (state->buttonLongLongPress) {
                demoLastSwitch = millis();
                setState(FSMState::DEMO);
            }

            nowEffect->update(knobValue);
            break;

        case FSMState::DEMO: 
            unsigned long now = millis();

            if (state->buttonClick || state->buttonDoubleClick) {
                setState(FSMState::MANUAL);
                break;
            }

            if (now - demoLastSwitch >= DEMO_INTERVAL) {
                demoLastSwitch = now;
                
                nowEffect = effectSequence.next();
                nowEffect->begin(leds, numLeds);
            }

            nowEffect->update(knobValue);

            break;
    }
}
