#ifndef DATA_H
#define DATA_H

#include <vector>
#include <initializer_list>

class Data
{
public:
    std::vector<double> inputs;
    int res;
public:
    Data(std::initializer_list<double> args);
};

extern std::vector<Data> dataset;


double cost(double result, double expected) {

}

double costDeriv(double result, double expected);


#endif // DATA_H
