#pragma once
#include "lorenz.hpp"

LorenzState eulerStepCompute(
    const LorenzState& state, const LorenzState& deriv, double dt);