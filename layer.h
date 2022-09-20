#ifndef LAYER_H
#define LAYER_H

#include "node.h"
#include <vector>

/**
 * @brief a node layer
 * 
 */
class Layer
{
public:
    std::vector<Node> nodes;

    Layer(int inputSize, int outputSize);

    /**
     * @brief 
     * 
     * @param input 
     * @return std::vector<double> 
     */
    std::vector<double> calculate(std::vector<double> input);


    std::vector<double> train(std::vector<double> input, Layer* nextLayer);
};

#endif // LAYER_H
