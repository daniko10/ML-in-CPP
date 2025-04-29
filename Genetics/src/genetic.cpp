#include "../include/utils.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using std::vector;
using utils::function;

namespace genetic
{

    Solution::Solution(const int &n)
    {
        for (int i = 0; i < n; i++)
        {
            const int bit = static_cast<double>(rand()) / RAND_MAX < 0.5 ? 1 : 0;
            bits.push_back(bit);
        }
    }

    double Solution::adaptation() const
    {
        const double sum = bin2int();
        return sum < 0.01 ? 0 : function(sum);
    }

    double Solution::bin2int() const
    {
        double sum = 0;
        int index = bits.size() - 1;
        std::for_each(bits.begin(), bits.end(), [&sum, &index](const int &bit)
                      { sum += bit * pow(2, index--); });

        sum /= pow(2, 16);
        return sum;
    }

    void Solution::mutation(const double &mutation_chance)
    {
        std::for_each(bits.begin(), bits.end(), [&mutation_chance](int &bit)
                      {
        if (static_cast<double>(rand()) / RAND_MAX < mutation_chance) {
            bit = bit ? 0 : 1;
        } });
    }

    void Solution::print_bits() const
    {
        std::for_each(bits.begin(), bits.end(), [](const int &bit)
                      { std::cout << bit << " "; });
        std::cout << std::endl;
    }

    int &Solution::get_bit(const int &index)
    {
        return bits[index];
    }

    std::pair<Solution, Solution> Solution::crossover(const Solution &secondParent) const
    {
        Solution first_child{secondParent};
        Solution second_child{*this};

        int random_crossover_index = static_cast<int>((double)(rand()) / RAND_MAX * (bits.size() - 2) + 1);

        for (int i = 0; i < random_crossover_index; i++)
        {
            const int temp = first_child.get_bit(i);
            first_child.get_bit(i) = second_child.get_bit(i);
            second_child.get_bit(i) = temp;
        }

        return {first_child, second_child};
    }

} // namespace genetic