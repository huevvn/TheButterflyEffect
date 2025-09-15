#include "../include/euler.hpp"

LorenzState eulerStepCompute(const LorenzState& state,
                             const LorenzState& deriv,
                             double dt) {
    LorenzState newState;
    newState.x = state.x + deriv.x * dt;
    newState.y = state.y + deriv.y * dt;
    newState.z = state.z + deriv.z * dt;
    return newState;
}