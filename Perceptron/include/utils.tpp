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
    const int sizeOfDataset = X.size();
    const int max_index = sizeOfDataset - 1;
    const int min_index = 0;
    const int test_size = static_cast<int>(sizeOfDataset * test_train_ratio);

    std::vector<int> assigned_indices{};

    while (assigned_indices.size() < test_size) {
        int index_to_allocate = min_index + std::rand() % (max_index - min_index + 1);

        if (std::find(assigned_indices.begin(), assigned_indices.end(), index_to_allocate) == assigned_indices.end()) {
            assigned_indices.push_back(index_to_allocate);
            X_test.push_back(X[index_to_allocate]);
            Y_test.push_back(Y[index_to_allocate]);
        }
    }

    for (int i = 0; i < sizeOfDataset; ++i) {
        if (std::find(assigned_indices.begin(), assigned_indices.end(), i) == assigned_indices.end()) {
            X_train.push_back(X[i]);
            Y_train.push_back(Y[i]);
        }
    }
}