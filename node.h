#ifndef NODE_H
#define NODE_H

#include <vector>
#include "data.h"

class Node
{
    std::vector<double> input;

    double result;
    double output;
    double nodeValue;

    double bias;
    std::vector<double> weights;

    double biasGrad;
    std::vector<double> weightsGrad;

public:

    Node(int inputSize);

    Node(double bias, std::vector<double> weights);

    double activation(double input);

    double activationDeriv(double input);

    double calculate(std::vector<double>& input);

    double train(std::vector<double>& input, double expected, std::vector<Node>& nextLayer, int thisIdx);

    void learn(double learnRate);

    double getNodeValue();
};

#endif // NODE_H
