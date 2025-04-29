#include <gtest/gtest.h>
#include "genetic.hpp"

using genetic::Solution;

TEST ( SolutionTests, constructors ) {
    Solution s1{13};
    Solution s2{{
        1, 0, 1, 0, 1, 0, 1, 0}};
    Solution s3{};

    EXPECT_EQ(s1.size(), 13);
    EXPECT_EQ(s2.size(), 8);
    EXPECT_EQ(s3.size(), 16);
}

TEST ( SolutionTests, adaptation ) {
    using utils::function;

    Solution s1{13};
    Solution s2{{
        1, 0, 1, 0, 1, 0, 1, 0}};
    Solution s3{};

    EXPECT_EQ(s1.adaptation(), function(s1.bin2int()));
    EXPECT_EQ(s2.adaptation(), function(s2.bin2int()));
    EXPECT_EQ(s3.adaptation(), function(s3.bin2int()));
}

TEST ( SolutionTests, mutation ) {
    double mutation_chance = 0;
    Solution s1{{
        1, 0, 1, 0, 1, 0, 1, 0}};
    Solution inverted_s1{{
        0, 1, 0, 1, 0, 1, 0, 1}};
    
    s1.mutation(mutation_chance);
    EXPECT_EQ(s1, s1);

    mutation_chance = 1.;
    s1.mutation(mutation_chance);
    EXPECT_EQ(s1, inverted_s1);
}

TEST ( SolutionTests, get_bit ) {
    int index = 0;
    Solution s1{{
        1, 0, 1, 0, 1, 0, 1, 0}};
    
    const auto& bits = s1.get_bits();
    std::for_each(bits.begin(), bits.end(), [&](const int& bit) {
        EXPECT_EQ(bit, s1.get_bit(index++));
    });
}