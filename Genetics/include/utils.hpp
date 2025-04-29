#pragma once

#include "genetic.hpp"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cmath>

namespace utils
{
    using genetic::Solution;
    using std::vector;
    double function(const double &x);

    vector<Solution> rulette_selection(
        const vector<Solution> &solutions,
        const int &population,
        const int &nmbr_of_parents);

    void save_n_best_solutions(
        std::vector<Solution> &solutions,
        const std::vector<Solution> &best,
        const int& n);
} // namespace utils