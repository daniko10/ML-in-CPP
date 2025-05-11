#include "../include/utils.hpp"
#include "../include/particle.hpp"

namespace utils {
double objective(const Particle& particle) {
    const auto [x, y] = std::tuple{particle.x, particle.y};
    return 2 * std::log(std::abs(x + 0.2) + 0.002)
         + std::log(std::abs(y + 0.1) + 0.001)
         + std::cos(3 * x)
         + 2 * std::pow(std::sin(3 * x * y), 2)
         + std::pow(std::sin(y), 2)
         - std::pow(x, 2)
         - 0.5 * std::pow(y, 2);
}

void find_best_global_particle(Particle& best_global_particle_position,
                               const std::vector<Particle>& best_local_particles_position,
                               double& z_global) {
    std::for_each(best_local_particles_position.begin(), best_local_particles_position.end(), 
    [&z_global, &best_global_particle_position] (const auto& particle) {
        const double z_local = objective(particle);
        if (z_local < z_global) {
            z_global = z_local;
            best_global_particle_position = particle;
        }
    });
}
}