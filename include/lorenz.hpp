#pragma once

struct LorenzState {
    double x, y, z;
};

struct LorenzParams {
    double sigma, beta, rho;
};

LorenzState lorenzCompute(const LorenzState& state, const LorenzParams& params);