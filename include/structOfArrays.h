#pragma once
#include <vector>

struct particlesSoA {
    std::vector<float> x, y, z, w;

    particlesSoA(size_t count) : x(count, 0.0f), y(count, 0.0f), z(count, 0.0f), w(count, 0.0f) {}
};

void processSoA(particlesSoA& particles) {
    for (size_t i = 0; i < particles.x.size(); ++i) {
        particles.x[i] += 1.0f;
        particles.y[i] += 1.0f;
        particles.z[i] += 1.0f;
        particles.w[i] += 1.0f;
    }
}