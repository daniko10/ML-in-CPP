#include "../include/utils.hpp"

void countClassesInstances(
    int& first_class_count,
    int& second_class_count,
    const std::vector<int>& Y)
{
    std::for_each(Y.begin(), Y.end(), [&first_class_count, &second_class_count](const int& y) {
        y == 0 ? first_class_count++ : second_class_count++;
    });
}