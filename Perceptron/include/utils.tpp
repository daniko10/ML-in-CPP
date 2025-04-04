#pragma once

#include "utils.hpp"

template <typename T>
void extractDataFromFile(
    std::vector<std::vector<T>>& X,
    std::vector<int>& Y,
    std::string filename,
    const std::array<std::string, 2>& class_names)
{
    std::ifstream file("../" + filename);
    std::string line{};

    while(std::getline(file, line)) {
        
        std::vector<double> x{};
        int y{};

        std::stringstream ss(line);
        std::string value{};
        
        while (std::getline(ss, value, ',')) {
            if (value == class_names[0] or value == class_names[1])
                y = value == class_names[0] ? 0 : 1;
            else
                x.push_back(std::stod(value)); 
        }
        X.push_back(x);
        Y.push_back(y);
    }
}

template <typename T>
void splitDataForTrainTestDataset(
    const std::vector<std::vector<T>>& X,
    const std::vector<int>& Y,
    std::vector<std::vector<T>>& X_train,
    std::vector<int>& Y_train,
    std::vector<std::vector<T>>& X_test,
    std::vector<int>& Y_test,
    const double test_train_ratio)
{
    srand(time(NULL));

    const int dataset_size = X.size();
    const int max_index = dataset_size - 1;
    const int min_index = 0;
    const int test_size = static_cast<int>(dataset_size * test_train_ratio);
    int first_class = 0;
    int second_class = 1;
    int first_class_counter = 0;
    int second_class_counter = 0;
    int first_class_size = 0;
    int second_class_size = 0;
    int first_class_size_test{};
    int second_class_size_test{};
    bool first_class_selected = true;
    const int max_attempts = 10000;
    int attempts = 0;

    countClassesInstances(first_class_size, second_class_size, Y);

    first_class_size_test = static_cast<int>(first_class_size * test_train_ratio);
    second_class_size_test = static_cast<int>(second_class_size * test_train_ratio);

    std::vector<int> assigned_indices{};

    while (assigned_indices.size() < test_size and attempts++ < max_attempts) {
        int index_to_allocate = min_index + std::rand() % (max_index - min_index + 1);

        if (Y[index_to_allocate] == first_class) {
            if (first_class_counter < first_class_size_test) {
                first_class_selected = true;
            }
            else {
                continue;
            }
        }
        else {
            if (second_class_counter < second_class_size_test) {
                first_class_selected = false;
            }
            else {
                continue;
            }
        }

        if (std::find(assigned_indices.begin(), assigned_indices.end(), index_to_allocate) == assigned_indices.end()) {
            assigned_indices.push_back(index_to_allocate);
            X_test.push_back(X[index_to_allocate]);
            Y_test.push_back(Y[index_to_allocate]);
            first_class_selected == true ? first_class_counter++ : second_class_counter++;
        }
    }

    for (int i = 0; i < dataset_size; ++i) {
        if (std::find(assigned_indices.begin(), assigned_indices.end(), i) == assigned_indices.end()) {
            X_train.push_back(X[i]);
            Y_train.push_back(Y[i]);
        }
    }
}