#ifndef DATA_H
#define DATA_H

#include <vector>
#include <initializer_list>

/**
 * @brief Data class to represent a data point, input and expected output
 * 
 */
class Data
{
public:
    std::vector<double> inputs;
    int expected;
public:
    Data(std::initializer_list<double> args);
};

extern std::vector<Data> dataset;

#endif // DATA_H
