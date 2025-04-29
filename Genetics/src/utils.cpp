#include "../include/utils.hpp"

namespace utils
{
    double function(const double &x)
    {
        return cos(80 * x + 3) + 3 * pow(x, -0.9) - 2;
    }

    vector<Solution> rulette_selection(
        const vector<Solution> &solutions,
        const int &population,
        const int &nmbr_of_parents)
    {
        if (population <= 0 || nmbr_of_parents <= 1 || population < nmbr_of_parents)
        {
            return {};
        }
        vector<Solution> parents{};
        vector<std::pair<double, double>> rulette_ranges{};
        vector<int> already_picked_solutions{};
        vector<double> adaptations{};
        double sum = 0;

        for (int i = 0; i < population; i++)
        {
            adaptations.push_back(solutions[i].adaptation());
        }

        std::for_each(adaptations.begin(), adaptations.end(), [&sum](const double &x)
                      { sum += x; });

        rulette_ranges.push_back({0, adaptations[0] / sum});

        for (int i = 1; i < solutions.size(); i++)
        {
            rulette_ranges.push_back({rulette_ranges[i - 1].second, adaptations[i] / sum + rulette_ranges[i - 1].second});
        }

        while (already_picked_solutions.size() < nmbr_of_parents)
        {
            const double rulette_random = (double)(rand()) / (RAND_MAX);
            for (int i = 0; i < solutions.size(); i++)
            {
                if (rulette_random >= rulette_ranges[i].first && rulette_random < rulette_ranges[i].second &&
                    std::find(already_picked_solutions.begin(), already_picked_solutions.end(), i) == already_picked_solutions.end())
                {
                    already_picked_solutions.push_back(i);
                    break;
                }
            }
        }

        std::for_each(already_picked_solutions.begin(), already_picked_solutions.end(), [&parents, &solutions](const int &i)
                      { parents.push_back(solutions[i]); });

        return parents;
    }

    void save_n_best_solutions(
        std::vector<Solution> &solutions,
        const std::vector<Solution> &best,
        const int& n)
    {
        if (solutions.size() < n or best.size() < n) {
            return;
        }

        for (int i = 0; i < n; i++)
        {
            solutions[i] = best[i];
        }
    }
} // namespace utils