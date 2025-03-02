#pragma once
#include <vector>

struct Particle {
    float x, y, z, w; // 16 bytes
};

void processAoS(std::vector<Particle>& particles) {
    for (auto& p : particles) {
        p.x += 1.0f;
        p.y += 1.0f;
        p.z += 1.0f;
        p.w += 1.0f;
    }
}