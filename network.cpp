#include "network.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include "node.h"

using namespace std;

double Network::cost(double result, double expected) {
    double error = result - expected;
    return error * error;
}

double Network::costDeriv(double result, double expected) {
    return 2 * (result - expected);
}

Network::Network(vector<int> size) {
    for (int i = 1; i < size.size(); ++i) {
        layers.emplace_back(size[i - 1], size[i]);
    }
}



vector<double> Network::classify(vector<double> input) {
    for (auto& layer : layers) {
        input = layer.calculate(input);
    }
    return input;
}

vector<vector<QColor>> Network::visualize() {
    vector<vector<QColor>> colors;
    for (int x = 0; x < 500; ++x) {
        colors.push_back(vector<QColor>());
        for (int y = 0; y < 500; ++y) {
            auto data = vector<double>{x / 500.0f, y / 500.0f};
            auto result = classify(data);

            int pred = max_element(result.begin(), result.end()) - result.begin();

            if (pred == 1) {
                colors[x].push_back(qRgb(0, 0, 0));
            } else {
                colors[x].push_back(qRgb(150, 150, 150));
            }
        }
    }
    return colors;
}

//void Network::setValues(vector<double> weights) {
//    int weights_idx = 0;
//    for (auto& layer : layers) {
//        for (auto& node : layer.nodes) {
//            for (int i = 0; i < node.weights.size(); ++i) {
//                node.weights[i] = weights[weights_idx];

//                if (weights_idx++ >= weights.size()) {
//                    return;
//                }
//            }
//            node.bias = weights[weights_idx];

//            if (weights_idx++ >= weights.size()) {
//                return;
//            }
//        }
//    }
//}

double Network::cost(vector<Data> dataset) {
    double cost;
    for (auto& data : dataset) {
        auto result = classify(data.inputs);

        for (int i = 0; i < result.size(); ++i) {
            cost += Network::cost(result[i], data.res == i ? 1 : 0);
        }
    }
    return cost;
}

double totalCost(Network* n, vector<Data> dataset) {

}

static random_device rd;
static mt19937 rng(rd());

vector<Data> randomSubset(vector<Data> dataset, unsigned int size) {
    uniform_int_distribution<> dist(0, dataset.size() - 1);
    set<unsigned int> indices;
    while (indices.size() < size) {
        indices.insert(dist(rng));
    }
    vector<Data> randDataset;
    for (int idx : indices) {
        randDataset.push_back(dataset[idx]);
    }
    return randDataset;
}

double learnRate = 0.05;
double delta = 0.001;
void Network::learn() {
    // random set of points
    vector<Data> randDataset = randomSubset(dataset, 30);

    double baseCost = totalCost(this, randDataset);

    cerr << baseCost << '\n';
    // for every weight, calc change in cost by change in weight
    for (auto& layer : layers) {
        for (auto& node : layer.nodes) {
            for (int i = 0; i < node.weights.size(); ++i) {
                node.weights[i] += delta;
                node.weightsGrad[i] = (totalCost(this, randDataset) - baseCost) / delta;
                node.weights[i] -= delta;
            }
            // gradiant for bias
            node.bias += delta;
            node.biasGrad = (totalCost(this, randDataset) - baseCost) / delta;
            node.bias -= delta;
        }
    }

    // apply all gradient
    for (auto& layer : layers) {
        for (auto& node : layer.nodes) {
            for (int i = 0; i < node.weights.size(); ++i) {
                node.weights[i] -= node.weightsGrad[i] * learnRate;
            }
            node.bias -= node.biasGrad * learnRate;
        }
    }
}

