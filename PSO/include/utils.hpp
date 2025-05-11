#pragma once

#include <vector>
#include <cmath>

struct Particle;

namespace utils {
double objective(const Particle& particle);
void find_best_global_particle(Particle& best_global_particle_position,
    const std::vector<Particle>& best_local_particles_position,
    double& z_global);
}