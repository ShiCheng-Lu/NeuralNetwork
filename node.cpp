#include "node.h"

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
        weightsGrad.push_back(0);
    }
    bias = 0;
    input.resize(inputSize);
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
    result = this->bias;
    for (int i = 0; i < weights.size(); ++i) {
        result += input[i] * weights[i];

        // save input for training
        this->input[i] = input[i];
    }
    return activation(result);
}

void Node::train(vector<Node>& nextLayer, int thisIdx) {
    nodeValue = 0;

    // for middle layers
    for (int i = 0; i < nextLayer.size(); ++i) {
        nodeValue += activationDeriv(result) * nextLayer[i].weights[thisIdx] * nextLayer[i].nodeValue;
    }

    for (int i = 0; i < weightsGrad.size(); ++i) {
        weightsGrad[i] += input[i] * nodeValue;
    }
    biasGrad += nodeValue;
}

void Node::learn(double learnRate) {
    // apply gradients
    for (int i = 0; i < weightsGrad.size(); ++i) {
        weights[i] -= weightsGrad[i] * learnRate;
    }
    bias -= biasGrad * learnRate;

    // clear gradients
    for (int i = 0; i < weightsGrad.size(); ++i) {
        weightsGrad[i] = 0;
    }
    biasGrad = 0;
}

double Node::getNodeValue() {
    return nodeValue;
}

