#include "node.h"

#include "network.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

static random_device rd;
static mt19937 rng(rd());
static uniform_real_distribution<> dis(-1.0, 1.0);

Node::Node(int inputSize) {
    // randomize weight and bias
    for (int i = 0; i < inputSize; ++i) {
        weights.push_back(dis(rng));
    }
    // bias = dis(rng);
}

Node::Node(double bias, std::vector<double> weights): bias{bias}, weights{weights} {}

double Node::activation(double input) {
    return 1 / (1 + exp(-input));
}

double Node::activationDeriv(double input) {
    double activ = activation(input);
    return activ * (1 - activ);
}

double Node::calculate(vector<double>& input) {
    double result = this->bias;
    for (int i = 0; i < weights.size(); ++i) {
        result += input[i] * weights[i];
    }
    output = activation(result);

    // for back propagation
    nodeValue = activationDeriv(result);
    return output;
}

void Node::learn(double expected, double learnRate) {
    nodeValue *= Network::costDeriv(output, expected);

    for (int i = 0; i < weights.size(); ++i) {

    }
}
