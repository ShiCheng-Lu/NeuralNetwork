#include "layer.h"

using namespace std;

Layer::Layer(int inputSize, int outputSize) {
    for (int i = 0; i < outputSize; ++i) {
        nodes.emplace_back(inputSize);
    }
}

vector<double> Layer::calculate(vector<double> input) {
    vector<double> ret;
    for (auto& node : nodes) {
        ret.push_back(node.calculate(input));
    }
    return ret;
}

void Layer::train(Layer* nextLayer) {
    for (int i = 0; i < nodes.size(); ++i) {
        nodes[i].train(nextLayer->nodes, i);
    }
}

void Layer::learn(double learnRate) {
    for (auto& node : nodes) {
        node.learn(learnRate);
    }
}
