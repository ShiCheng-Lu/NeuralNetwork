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
public: // for testing leave everyone public for now
    std::vector<Node> nodes;

    Layer(int inputSize, int outputSize);

    /**
     * @brief 
     * 
     * @param input 
     * @return std::vector<double> 
     */
    std::vector<double> calculate(std::vector<double> input);


    void train(Layer* nextLayer);

    void learn(double learnRate);
};

#endif // LAYER_H
