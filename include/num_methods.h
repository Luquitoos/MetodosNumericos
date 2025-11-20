#ifndef NUM_METHODS_H
#define NUM_METHODS_H
#include <vector> 

double newton_raphson_method(std::vector<double>* values_d, double a, double d, int max, const double tolerance);
double newton_modified_method(double a, double d); 
double secant_method(std::vector<double>* values_d, double a, double d1, double d2, int max, const double tolerance);

#endif