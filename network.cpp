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

Network::Network(vector<int> size): mockLayer{size.back(), 1} {
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

double Network::cost(vector<Data> dataset) {
    double cost;
    for (auto& data : dataset) {
        auto result = classify(data.inputs);

        for (int i = 0; i < result.size(); ++i) {
            cost += Network::cost(result[i], data.expected == i ? 1 : 0);
        }
    }
    return cost;
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
void Network::learn() {
    // random set of points
    // vector<Data> randDataset = randomSubset(dataset, 30);

    for (auto& data : dataset) {
        auto res = classify(data.inputs);

        // set dummy layer's values
        mockLayer.nodes[0].nodeValue = 1;
        for (int i = 0; i < mockLayer.nodes[0].weights.size(); ++i) {
            mockLayer.nodes[0].weights[i] = costDeriv(res[i], i == data.expected ? 1 : 0);
        }

        layers[layers.size() - 1].train(&mockLayer);
        // back prop
        for (int i = layers.size() - 2; i >= 0; --i) {
            layers[i].train(&layers[i + 1]);
        }
    }
    // apply gradient descent
    for (auto& layer : layers) {
        layer.learn(learnRate);
    }
}

void Network::print() {
    for (int l = 0; l < layers.size(); ++l) {
        for (int n = 0; n < layers[l].nodes.size(); ++n) {
            auto& node = layers[l].nodes[n];
            cout << "l" << l << 'n' << n;
            for (auto& w: node.weights) {
                cout << " " << w;
            }
            cout << ' ' << node.bias << endl;
        }
    }
    cout << "Cost: " << cost(dataset) << endl;
}

