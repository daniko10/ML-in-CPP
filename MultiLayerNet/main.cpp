#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <ctime>
#include <optional>
#include <cmath>

double act_fun(const double& x) {
    return 1. / (1 + 1. / pow(M_E, x));
}

class Neuron;

template <typename T>
class MLP
{
public:
    MLP(
        const std::vector<int> &layers,
        const double& lr) : _layers(layers), _lr(lr)
    {
        assert(_layers.size() > 2);
        assert(std::find(layers.begin(), layers.end(), 0) == layers.end());

        for (int i = 0; i < layers.size(); i++)
        {
            _net.push_back(std::vector<Neuron>());

            for (int j = 0; j < layers[i]; j++)
            {
                if (i == layers.size() - 1)
                {
                    _net[i].push_back(Neuron(j, 0, std::optional<std::reference_wrapper<std::vector<Neuron>>>{_net[i-1]}));
                }
                else if (i == 0) {
                    _net[i].push_back(Neuron(j, layers[i + 1]));
                }
                else {
                    _net[i].push_back(Neuron(j, layers[i + 1], std::optional<std::reference_wrapper<std::vector<Neuron>>>{_net[i-1]}));
                }
            }
        }
    }

    void train(
        const std::vector<std::vector<T>> &X,
        const std::vector<std::vector<int>> &Y)
    {
        int index = 0;
        for(const auto& x : X) {
            std::vector<std::vector<double>> weights_sum_act{};
            for (int i = 1; i < _net.size(); i++) {
                weights_sum_act.push_back(std::vector<double>{});
                for (int j = 0; j < _net[i].size(); j++) {
                    auto& neuron = _net[i][j];
                    if (i == 1) {
                        weights_sum_act[i-1].push_back(neuron.calculate_weights_sum_act(x));
                    }
                    else {
                        weights_sum_act[i-1].push_back(neuron.calculate_weights_sum_act(weights_sum_act[i-2]));
                    }
                    std::cout << weights_sum_act[i-1][j] << " ";
                }
                std::cout << std::endl;
            }
            std::vector<double> loss_errors = weights_sum_act[_net.size() - 2];
            for( int j = 0; j < loss_errors.size(); j++) {
                loss_errors[j] = 1. / 2 * pow((loss_errors[j] - Y[index][j]), 2);
                std::cout<<loss_errors[j]<<" ";
            }
            index++;
        }
    }

    void print_model() const
    {
        int layer_index = 0;
        for (int i = 0; i < _layers.size(); i++)
        {
            std::cout << "Layer: " << layer_index++ << std::endl;
            for (int j = 0; j < _layers[i]; j++)
            {
                std::cout << "Neuron: " << j << "\t";
                _net[i][j].print_weights_next();
                if (i != 0) {
                    std::cout << "\t";
                    _net[i][j].print_weights_prev();
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

private:
    std::vector<int> _layers{};
    std::vector<std::vector<Neuron>> _net{};
    double _lr{};
};

class Neuron
{
public:
    Neuron(const int index,
           const int neuron_next_layer = 0,
           std::optional<std::reference_wrapper<std::vector<Neuron>>> previous_layer = std::nullopt) : index_in_layer(index)
    {
        for (int i = 0; i < neuron_next_layer; i++)
        {
            _weights_next.push_back(static_cast<double>(rand()) / RAND_MAX);
        }

        if (previous_layer) {
            const auto& previous_layer_value = previous_layer->get();
            for(int i = 0; i < previous_layer_value.size(); i++) {
                _weights_prev.push_back(&previous_layer_value[i]._weights_next[index_in_layer]);
            }
        }
    }

    double calculate_weights_sum_act(const std::vector<double>& x) const {
        double sum = 0;
        int index = 0;
        std::for_each(x.begin(), x.end(), [&sum, &index, this](const double& val) { sum += val * *_weights_prev[index++]; });
        sum += _bias;

        return act_fun(sum);
    }

    void print_weights_next() const
    {
        std::for_each(_weights_next.begin(), _weights_next.end(), [](const double &x)
                      { std::cout << x << " "; });
    }

    void print_weights_prev() const
    {
        std::for_each(_weights_prev.begin(), _weights_prev.end(), [](const double *x)
                      { std::cout << *x << " "; });
    }

private:
    const int index_in_layer;
    std::vector<double> _weights_next{};
    std::vector<const double*> _weights_prev;
    double _bias{1};
};

int main()
{
    srand(time(nullptr));
    MLP<double> mlp({4, 7, 11, 2}, 0.01);

    std::vector<std::vector<double>> X{{1, 2, 3, 4}};
    std::vector<std::vector<int>> Y{{1, 0}};

    mlp.train(X, Y);

    mlp.print_model();
}