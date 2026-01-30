#include "EffectSequence.h"
#include "Firefly.cpp"
#include "Bulbs.cpp"
#include "Wave.cpp"

EffectSequence::EffectSequence() {
    sequence[0] = new Firefly();
    sequence[1] = new Bulbs();
    sequence[2] = new Wave();
    idx = 0;
}

Effect* EffectSequence::next() {
    idx = (idx + 1) % EFFECT_COUNT;
    return sequence[idx];
}

Effect* EffectSequence::prev() {
    idx = (idx == 0) ? EFFECT_COUNT - 1 : idx - 1;
    return sequence[idx];
}

Effect* EffectSequence::current() {
    return sequence[idx];
}
