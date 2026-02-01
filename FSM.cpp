#include "FSM.h"

FSM::FSM(EffectSequence& effectSequence, Effect*& nowEffect, CRGB* leds, uint16_t NUM_LEDS)
    : fsmState(FSMState::MANUAL),
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

void FSM::update(InputState& state) {
    switch (fsmState) {

        case FSMState::LOAD:
            // todo begin anim. and block click
            break;

        case FSMState::AUTO:
            // todo auto
            break;

        case FSMState::MANUAL:
            if (state.buttonClick) {
                nowEffect = effectSequence.next();
                nowEffect->begin(leds, numLeds);
            } 
            else if (state.buttonDoubleClick) {
                nowEffect = effectSequence.prev();
                nowEffect->begin(leds, numLeds);
            } 
            else if (state.buttonLongPress) {
                // todo -> add/rm fav.
            }
            else if (state.buttonLongLongPress) {
                // todo -> demo
            }

            uint16_t knobValue = state.knobAngle;
            nowEffect->update(knobValue);
            break;

        case FSMState::DEMO:
            // all anim. auto run
            break;
    }
}
