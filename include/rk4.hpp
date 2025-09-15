#pragma once
#include "lorenz.hpp"

LorenzState rk4StepCompute
(const LorenzState& state, const LorenzState& k1,
const LorenzParams& params, double dt);
