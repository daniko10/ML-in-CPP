#include "../include/particle.hpp"

Particle::Particle(double x, double y) : x(x), y(y) {}
Particle::Particle(double x_down, double x_up,
                   double y_down, double y_up) 
{
    if (!x_down_limit) x_down_limit = x_down;
    if (!x_up_limit)   x_up_limit   = x_up;
    if (!y_down_limit) y_down_limit = y_down;
    if (!y_up_limit)   y_up_limit   = y_up;
    x = ((double) rand()) / (RAND_MAX) * (x_up - x_down) + x_down;
    y = ((double) rand()) / (RAND_MAX) * (y_up - y_down) + y_down;
}

Particle Particle::operator-(const Particle& particle) const {
    Particle pTemp = {x - particle.x, y - particle.y};
    pTemp.cast();
    return pTemp;
}

Particle Particle::operator+(const Particle& particle) const {
    Particle pTemp = {x + particle.x, y + particle.y};
    pTemp.cast();
    return pTemp;
}

Particle Particle::operator+=(const Particle& particle) {
    x += particle.x;
    y += particle.y;
    cast();
    return *this;
}

Particle& Particle::operator=(const Particle& particle) {
    x = particle.x;
    y = particle.y;
    return *this;
}

bool Particle::operator>(const Particle& particle) {
    using utils::objective;
    if (objective(*this) > objective(particle)) {
        return true;
    }
    return false;
}

void Particle::update_if_better(const Particle& particle) {
    if(*this > particle) {
        *this = particle;
    }
}

void Particle::cast() {
    x = x < x_down_limit.value() ? x_down_limit.value() : x > x_up_limit.value() ? x_up_limit.value() : x;
    y = y < y_down_limit.value() ? y_down_limit.value() : y > y_up_limit.value() ? y_up_limit.value() : y;
}

Particle operator*(const double wsp, const Particle& particle) {
    Particle pTemp = {particle.x * wsp, particle.y * wsp};
    pTemp.cast();
    return pTemp;
}

std::ostream& operator<<(std::ostream& os, const Particle& particle) {
    os << "x=" << particle.x << ", y=" << particle.y << ", fun=" << utils::objective(particle);
    return os;
}

std::optional<double> Particle::x_down_limit = std::nullopt;
std::optional<double> Particle::x_up_limit   = std::nullopt;
std::optional<double> Particle::y_down_limit = std::nullopt;
std::optional<double> Particle::y_up_limit   = std::nullopt;