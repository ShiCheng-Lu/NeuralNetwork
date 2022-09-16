#ifndef NODE_H
#define NODE_H

#include <vector>

class Node
{
    double output;
    double nodeValue;

public:
    double bias;
    std::vector<double> weights;

    Node(int inputSize);

    Node(double bias, std::vector<double> weights);

    double activation(double input);

    double activationDeriv(double input);

    double calculate(std::vector<double>& input);

    // apply gradient descent
    void learn(double expected, double learnRate);
};

#endif // NODE_H
