#include <iostream> 
#include <vector>
#include "math_utils.cpp"
#include <cmath>
using namespace std;

// function: f(d) = a*e^d -4d^2
//a = 1
//d = 0.5

void newton_raphson_method(vector<double>* values_d, double a, double d, int max, const double tolerance) {
    values_d->push_back(d);
    double val = values_d->back();
    values_d->push_back(val - function_value(a, val)/derivate_function(a,val));
    int i = 0;
    while ((max>i)&&(abs(values_d->back() - (*values_d)[values_d->size()- 2]) >= tolerance )) {
        val = values_d->back();
        values_d->push_back(val - function_value(a, val)/derivate_function(a,val));
        i++;
    }
    if (i >= max) {
        cout << "The result doesn't converge with that interation limit\n";
    }
}

/*
double newton_modified_method(double a, double d) {

}

*/

void secant_method(vector<double>* values_d, double a, double d1, double d2, int max, const double tolerance) {
    values_d->push_back(d1);
    values_d->push_back(d2);
    int i = 0;
    while ((i < max)&& (abs(values_d->back()-(*values_d)[values_d->size()-2]) >= tolerance)) {
        d1 = (*values_d)[values_d->size()-2];//penultimo
        d2 = values_d->back();//ultimo
        values_d->push_back(d2-((function_value(a, d2)*(d2-d1))/(function_value(a, d2)-function_value(a, d1))));
        i++;
    }
}

