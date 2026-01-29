#include "EffectSequence.h"
#include "Firefly.cpp"

EffectSequence::EffectSequence() {
    sequence[0] = new Firefly();
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
