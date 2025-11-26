#ifndef NUM_METHODS_H
#define NUM_METHODS_H
#include <vector> 
using namespace std;

void newton_raphson_method(vector<double>* values_d, double a, double d, int max, const double tolerance);
void newton_modified_method(vector<double>* values_d, double a, double d, int max, const double tolerance); 
void secant_method(vector<double>* values_d, double a, double d1, double d2, int max, const double tolerance);

#endif