#pragma once
#include "InputState.h"

class Input {
  public:
    virtual ~Input() {};
    virtual void begin() {}
    virtual void update() = 0;    // update - clear state
    virtual const InputState& getState() const = 0;
};