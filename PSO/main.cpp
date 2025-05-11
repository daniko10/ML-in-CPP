#include "include/utils.hpp"
#include "include/particle.hpp"

int main() {
    using utils::find_best_global_particle;
    srand(time(nullptr));
    std::vector<Particle> particles{};
    std::vector<Velocity> velocities{};
    std::vector<Particle> best_local_particles_position{};
    Particle best_global_particle_position{};
    double z_global = std::numeric_limits<double>::infinity();
    
    constexpr double w = 0.5, c1 = 1, c2 = 2;
    constexpr int population = 50, iterations = 100;

    for (int i = 0; i < population; i++) {
        particles.push_back({-1, 1, -1, 1});
        velocities.push_back({});
    }

    best_local_particles_position = particles;
    find_best_global_particle(best_global_particle_position, best_local_particles_position, z_global);

    for (int i = 0; i < iterations; i++) {
        const double r1 = ((double) rand()) / RAND_MAX;
        const double r2 = ((double) rand()) / RAND_MAX;
        for (int j = 0; j < population; j++) {
            velocities[j] = w*velocities[j] + c1 * r1 * (best_local_particles_position[j] - particles[j]) + c2 * r2 * (best_global_particle_position - particles[j]);
            particles[j] += velocities[j];
            best_local_particles_position[j].update_if_better(particles[j]);
        }
        find_best_global_particle(best_global_particle_position, best_local_particles_position, z_global);
    }

    std::cout << "Global best solution: " << best_global_particle_position << std::endl; 

    return 0;
}