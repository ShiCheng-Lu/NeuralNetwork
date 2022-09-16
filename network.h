#ifndef NETWORK_H
#define NETWORK_H

#include "data.h"
#include "layer.h"
#include <vector>
#include <QColor>

class Network {

    std::vector<Layer> layers;

public:
    static double cost(double result, double expected);

    static double costDeriv(double result, double expected);

    Network(std::vector<int> nodeCount);

    std::vector<double> classify(std::vector<double> input);

    std::vector<std::vector<QColor>> visualize();

    void setValues(std::vector<double> weights);

    double cost(std::vector<Data> dataset);

    void learn();
};

#endif // NETWORK_H
