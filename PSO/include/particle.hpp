#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <optional>
#include <algorithm>
#include "../include/utils.hpp"

struct Particle 
{
    Particle(double x = 0, double y = 0);
    Particle(double x_down, double x_up,
             double y_down, double y_up);

    Particle operator-(const Particle& particle) const;
    Particle operator+(const Particle& particle) const;
    Particle operator+=(const Particle& particle);
    Particle& operator=(const Particle& particle);
    bool operator>(const Particle& particle);
    void update_if_better(const Particle& particle);

    friend Particle operator*(const double wsp, const Particle& particle);
    friend double utils::objective(const Particle& particle);
    friend std::ostream& operator<<(std::ostream& os, const Particle& particle);

private:
    void cast();
    static std::optional<double> x_down_limit, x_up_limit;
    static std::optional<double> y_down_limit, y_up_limit;
    double x{};
    double y{};
};

using Velocity = Particle;