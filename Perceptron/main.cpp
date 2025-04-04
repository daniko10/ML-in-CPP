#include "include/perceptron.hpp"
#include "include/utils.hpp"
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(NULL));

    Perceptron<double> perceptron(3, 0.01);

    std::vector<std::vector<double>> X{};
    std::vector<int> Y{};

    std::vector<std::vector<double>> X_train{};
    std::vector<int> Y_train{};

    std::vector<std::vector<double>> X_test{};
    std::vector<int> Y_test{};

    const std::string first_class_name = "A";
    const std::string second_class_name = "B";

    extractDataFromFile(X, Y, "fuel.txt", std::array{first_class_name, second_class_name});
    splitDataForTrainTestDataset(X, Y, X_train, Y_train, X_test, Y_test, 0.2);
    
    std::cout << "Train size: " << X_train.size() << ", Test size: " << X_test.size() << std::endl;

    perceptron.train(X_train, Y_train, 1);
    perceptron.test(X_test, Y_test);
}