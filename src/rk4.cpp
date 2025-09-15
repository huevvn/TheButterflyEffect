#include "../include/rk4.hpp"   // includes lorenz.hpp via rk4.hpp

LorenzState rk4StepCompute(const LorenzState& state,
                           const LorenzState& k1,
                           const LorenzParams& params,
                           double dt) {

    // s2 = state + (dt / 2) * k1
    LorenzState s2 {
        state.x + 0.5 * dt * k1.x,
        state.y + 0.5 * dt * k1.y,
        state.z + 0.5 * dt * k1.z
    };
    LorenzState k2 = lorenzCompute(s2, params);

    // s3 = state + (dt / 2) * k2
    LorenzState s3 {
        state.x + 0.5 * dt * k2.x,
        state.y + 0.5 * dt * k2.y,
        state.z + 0.5 * dt * k2.z
    };
    LorenzState k3 = lorenzCompute(s3, params);

    // s4 = state + dt * k3
    LorenzState s4 {
        state.x + dt * k3.x,
        state.y + dt * k3.y,
        state.z + dt * k3.z
    };
    LorenzState k4 = lorenzCompute(s4, params); // derivative at s4

    // combine: newState = state + (dt / 6) * (k1 + 2 * k2 + 2 * k3 + k4)
    LorenzState newState {
        state.x + (dt / 6.0) * (k1.x + 2.0 * k2.x + 2.0 * k3.x + k4.x),
        state.y + (dt / 6.0) * (k1.y + 2.0 * k2.y + 2.0 * k3.y + k4.y),
        state.z + (dt / 6.0) * (k1.z + 2.0 * k2.z + 2.0 * k3.z + k4.z)
    };

    return newState;
}
