#ifndef LAYER_H
#define LAYER_H

#include "node.h"
#include <vector>

class Layer
{
public:
    std::vector<Node> nodes;

    Layer(int inputSize, int outputSize);

    std::vector<double> calculate(std::vector<double> input);
};

#endif // LAYER_H
