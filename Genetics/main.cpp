#include "include/utils.hpp"
#include "include/genetic.hpp"

int main()
{
    // I want to find a maximum of given function in a range [0.01,1]

    using genetic::Solution;
    using utils::rulette_selection;
    using utils::save_n_best_solutions;
    using std::vector;

    srand(time(nullptr));

    const int population = 100;
    const int iterations = 1000;
    const int nmbr_of_parents = population / 2;
    const double mutation_chance = 0.5;
    vector<Solution> solutions{};

    for (int i = 0; i < population; i++)
    {
        solutions.push_back(Solution());
    }

    for (int j = 0; j < iterations; j++)
    {
        vector<Solution> parents = rulette_selection(solutions, population, nmbr_of_parents);
        vector<Solution> children{};

        for (int i = 0; i < parents.size(); i++)
        {
            const auto local_children = parents[i].crossover(parents[(i + 1) % nmbr_of_parents]);
            children.push_back(local_children.first);
            children.push_back(local_children.second);
        }

        std::for_each(children.begin(), children.end(), [&mutation_chance](Solution &child)
                      { child.mutation(mutation_chance); });

        vector<Solution> best = solutions;
        std::sort(best.begin(), best.end(), [](const Solution &a, const Solution &b)
                  { return a.adaptation() > b.adaptation(); });
        std::sort(children.begin(), children.end(), [](const Solution &a, const Solution &b)
                  { return a.adaptation() < b.adaptation(); });

        solutions = children;
        save_n_best_solutions(solutions, best, 10);
    }

    std::cout << "Our maximum f(x_max): " << solutions[0].adaptation() << ", x_max: " << solutions[0].bin2int() << std::endl;
}