#ifndef NETWORK_H
#define NETWORK_H

#include "data.h"
#include "layer.h"
#include <vector>
#include <QColor>

class Network {
public: // for testing leave everyone public for now
    std::vector<Layer> layers;

    // dummy last layer that provide cost deriv as weight * nodeValue
    Layer mockLayer;

public:
    static double cost(double result, double expected);

    // how does change in result affect change in cost
    static double costDeriv(double result, double expected);

    Network(std::vector<int> nodeCount);

    std::vector<double> classify(std::vector<double> input);

    std::vector<std::vector<QColor>> visualize();

    void setValues(std::vector<double> weights);

    double cost(std::vector<Data> dataset);

    void learn();

    void print();
};

#endif // NETWORK_H
