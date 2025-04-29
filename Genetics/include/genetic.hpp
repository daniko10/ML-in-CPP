#pragma once

#include <vector>
#include <utility>

namespace utils {
    double function(const double& x);
}

namespace genetic {
    class Solution {
    public:
        Solution(const int& n = 16);

        double adaptation() const;
        double bin2int() const;
        void mutation(const double& mutation_chance);
        void print_bits() const;
        int& get_bit(const int& index);
        std::pair<Solution, Solution> crossover(const Solution& secondParent) const;

    private:
        std::vector<int> bits{};
    };
} //namespace genetic
