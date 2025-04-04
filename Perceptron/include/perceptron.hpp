#pragma once

#include <iostream>
#include <vector>

template <typename T = int>
class Perceptron {
    public:
        Perceptron(
            int inputs,
            double learning_rate
        );
        void train(
            const std::vector<std::vector<T>>& X_train,
            const std::vector<int>& Y_train,
            const int& epochs);
        void test(
            const std::vector<std::vector<T>>& X_test,
            const std::vector<int>& Y_test) const;

    private:
        const double calculateWeightSum(
            const std::vector<T>& x_train) const;
        const int calculateActFunVal(
            const double& sum) const;
        const int calculateLossValue(
            const int& y_true,
            const int& y_pred) const;
        void updateWeights(
            const std::vector<T>& x_train,
            const int& loss_value);

        int _nmbr_of_inputs{};
        double _bias{1};
        double _lr{};
        std::vector<double> _weights{};
};

#include "perceptron.tpp"