#ifndef NUM_METHODS_H
#define NUM_METHODS_H
#include <vector> 

void newton_raphson_method(std::vector<double>* values_d, double a, double d, int max, const double tolerance);
void newton_modified_method(std::vector<double>* values_d, double a, double d, int max, const double tolerance); 
void secant_method(std::vector<double>* values_d, double a, double d1, double d2, int max, const double tolerance);

#endif