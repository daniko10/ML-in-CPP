#include "perceptron.hpp"

template <typename T>
Perceptron<T>::Perceptron(
    int inputs,
    double learning_rate) : _nmbr_of_inputs(inputs), _lr(learning_rate) 
{
    srand(time(NULL));
    for(int i=0; i< inputs; i++)
        _weights.push_back((double) rand() / RAND_MAX);
}

template <typename T>
void Perceptron<T>::train(
    const std::vector<std::vector<T>>& X_train,
    const std::vector<int>& Y_train,
    const int& epochs) 
{
    double train_accuracy = 0;
    int index = 0;
    for (int epoch = 1; epoch <= epochs; epoch++) {
        train_accuracy = 0;
        index = 0;
        for(const auto& x_train : X_train) {
            const double sum = calculateWeightSum(x_train);
            const int fun_value = calculateActFunVal(sum);
            const int loss_value = calculateLossValue(Y_train[index], fun_value);

            std::cout<<"sum: "<< sum << ", fun_value: " << fun_value << ", loss: " << loss_value << std::endl;

            if (fun_value == Y_train[index])
                train_accuracy += 1;
            else
                updateWeights(x_train, loss_value);
            
            index++;
        }
        std::cout << "Train accuracy: " << train_accuracy / X_train.size() * 100 << "%, epoch: " << epoch << std::endl;
    }
}

template <typename T>
void Perceptron<T>::test(
    const std::vector<std::vector<T>>& X_test,
    const std::vector<int>& Y_test) const
{
    double test_accuracy = 0;
    int index = 0;
    for(const auto& x_test : X_test) {
        const double sum = calculateWeightSum(x_test);
        const int fun_value = calculateActFunVal(sum);
        const int loss_value = calculateLossValue(Y_test[index], fun_value);

        if (fun_value == Y_test[index])
            test_accuracy += 1;

        index++;
    }

    std::cout << "Test accuracy: " << test_accuracy / X_test.size() * 100 << "%" << std::endl;
}

template <typename T>
const double Perceptron<T>::calculateWeightSum(
    const std::vector<T>& x_train) const
{
    double weightSum = 0;
    for (int i=0; i<_nmbr_of_inputs; i++) {
        weightSum += _weights[i]*x_train[i];               
    }
    weightSum += _bias;

    return weightSum;
}

template <typename T>
const int Perceptron<T>::calculateActFunVal(
    const double& sum) const
{
    return sum >= 0 ? 1 : 0;
}

template <typename T>
const int Perceptron<T>::calculateLossValue(
    const int& y_true,
    const int& y_pred) const
{
    return y_true - y_pred;
}

template <typename T>
void Perceptron<T>::updateWeights(
    const std::vector<T>& x_train,
    const int& loss_value)
{
    _bias = _bias + _lr * loss_value;

    for(int i=0; i < _nmbr_of_inputs; i++) {
        _weights[i] = _weights[i] + _lr * loss_value * x_train[i];
    }

    std::cout << " Weights are updated!\n";
}