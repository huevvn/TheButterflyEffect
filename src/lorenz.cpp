#include "../include/lorenz.hpp"

LorenzState lorenzCompute(const LorenzState& state, const LorenzParams& params) {
    double dx = params.sigma * (state.y - state.x);
    double dy = state.x * (params.rho - state.z) - state.y;
    double dz = (state.x * state.y) - (params.beta * state.z);

    return {dx, dy, dz};
}