#include "utils.hpp"
#include "genetic.hpp"
#include <gtest/gtest.h>

using namespace testing;
using namespace genetic;
using namespace utils;

TEST( utilsTests, save_n_best_solutions_n_less_than_both_sizes)
{
    Solution dummy_actual{{1,1,1,1}};
    Solution dummy_prev_best_1{{1,0,0,0}};
    Solution dummy_prev_best_2{{1,1,0,0}};
    
    std::vector<Solution> solutions = {
        dummy_actual,
        dummy_actual,
        dummy_actual};
    std::vector<Solution> best = {
        dummy_prev_best_1,
        dummy_prev_best_2};

    save_n_best_solutions(solutions, best, 2);
    EXPECT_EQ(solutions[0], best[0]);
    EXPECT_EQ(solutions[1], best[1]);
    EXPECT_EQ(solutions[2], dummy_actual);
}

TEST( utilsTests, save_n_best_solutions_n_greater_than_sizes)
{
    Solution dummy_actual{{1,1,1,1}};
    Solution dummy_prev_best_1{{1,0,0,0}};
    Solution dummy_prev_best_2{{1,1,0,0}};
    
    std::vector<Solution> solutions = {
        dummy_actual,
        dummy_actual,
        dummy_actual};
    std::vector<Solution> best = {
        dummy_prev_best_1,
        dummy_prev_best_2};

    save_n_best_solutions(solutions, best, 4);
    EXPECT_EQ(solutions[0], dummy_actual);
    EXPECT_EQ(solutions[1], dummy_actual);
    EXPECT_EQ(solutions[2], dummy_actual);
}

TEST( utilsTests, rulette_selection_get_parents)
{
    Solution dummy_actual{{1,1,1,1}};
    Solution dummy_prev_best_1{{1,0,0,0}};
    Solution dummy_prev_best_2{{1,1,0,0}};
    
    std::vector<Solution> solutions = {
        dummy_actual,
        dummy_prev_best_1,
        dummy_prev_best_2};

    const auto parents = rulette_selection(solutions, 3, 2);
    EXPECT_EQ(parents.size(), 2);
}

TEST ( utilsTests, rulette_selection_nmbr_of_parents_greater_than_population)
{
    Solution dummy_actual{{1,1,1,1}};
    Solution dummy_prev_best_1{{1,0,0,0}};
    Solution dummy_prev_best_2{{1,1,0,0}};
    
    std::vector<Solution> solutions = {
        dummy_actual,
        dummy_prev_best_1,
        dummy_prev_best_2};

    const auto parents = rulette_selection(solutions, 3, 4);
    EXPECT_EQ(parents.size(), 0);
}

TEST ( utilsTests, rulette_selection_one_parent)
{
    Solution dummy_actual{{1,1,1,1}};
    Solution dummy_prev_best_1{{1,0,0,0}};
    Solution dummy_prev_best_2{{1,1,0,0}};
    
    std::vector<Solution> solutions = {
        dummy_actual,
        dummy_prev_best_1,
        dummy_prev_best_2};

    const auto parents = rulette_selection(solutions, 3, 1);
    EXPECT_EQ(parents.size(), 0);
}

