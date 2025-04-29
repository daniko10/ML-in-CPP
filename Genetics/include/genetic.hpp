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
        Solution(const std::vector<int> bits) : bits(bits) {}

        double adaptation() const;
        double bin2int() const;
        void mutation(const double& mutation_chance);
        void print_bits() const;
        int& get_bit(const int& index);
        std::pair<Solution, Solution> crossover(const Solution& secondParent) const;
        int size() const { return bits.size(); }
        const std::vector<int>& get_bits() const { return bits; } 

        bool operator==(const Solution& rhs) const;

    private:
        std::vector<int> bits{};
    };
} //namespace genetic
