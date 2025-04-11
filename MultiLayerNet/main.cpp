#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <ctime>

class Neuron;

template <typename T>
class MLP {
    public:
        MLP(
            const std::vector<int>& layers
        ) : _layers(layers) {
            assert(_layers.size() > 2);
            assert(std::find(layers.begin(), layers.end(), 0) == layers.end());

            for (int i = 0; i < layers.size(); i++) {
                _net.push_back(std::vector<Neuron>());

                for (int j = 0; j < layers[i]; j++) {
                    if (i == layers.size() - 1) {
                        _net[i].push_back(Neuron());
                    }
                    else {
                        _net[i].push_back(Neuron(layers[i+1]));
                    }
                }
            }
        }
        
        void print_model() const {
            int layer_index = 0;
            for (int i = 0; i < _layers.size(); i++) {
                std::cout << "Layer: " << layer_index++ << std::endl;
                for (int j = 0; j < _layers[i]; j++) {
                    std::cout << "Neuron: " << j << "\t";
                    _net[i][j].print_weights();
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
            
        } 
    
    private:
        std::vector<int> _layers{};
        std::vector<std::vector<Neuron>> _net{};
};

class Neuron {
    public:
        Neuron(const int neuron_next_layer = 0) {
            for (int i = 0; i < neuron_next_layer; i++) {
                _weights.push_back(static_cast<double>(rand()) / RAND_MAX);
            }
        }
        
        void print_weights() const {
            std::for_each(_weights.begin(), _weights.end(), [](const double& x) { std::cout << x << " ";});
        }

    private:
        std::vector<double> _weights{};
};

int main() {
    srand(time(nullptr));
    MLP<int> mlp({10, 7, 2});

    mlp.print_model();
}