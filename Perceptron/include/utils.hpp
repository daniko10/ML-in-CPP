# pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>

template <typename T>
void extractDataFromFile(
    std::vector<std::vector<T>>& X,
    std::vector<int>& Y,
    std::string filename,
    const std::array<std::string, 2>& class_names);

template <typename T>
void splitDataForTrainTestDataset(
    const std::vector<std::vector<T>>& X,
    const std::vector<int>& Y,
    std::vector<std::vector<T>>& X_train,
    std::vector<int>& Y_train,
    std::vector<std::vector<T>>& X_test,
    std::vector<int>& Y_test,
    const double test_train_ratio = 0.2);

void countClassesInstances(
    int& first_class_count,
    int& second_class_count,
    const std::vector<int>& Y);

#include "utils.tpp"