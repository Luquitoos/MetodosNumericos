#include <iostream>
#include "../include/math_utils.h"
#include <cmath>
#include <string>
using namespace std;

// that function calculates the derivative of f(d) = a*e^d - 4d^2 at d

double function_value(double a, double d) {
    return ((a * exp(d)) - (4 * pow(d, 2)));
}

// derivada que funciona pra qualquer função, porém, gasta mais poder computacional
double derivate(double a, double d) {
    int cont = 0;
    double h = 0.1;
    double val_d1 = (function_value(a, d+h)-function_value(a,d-h))/(2*h);

    h /= 10;
    double val_d2 = (function_value(a, d+h)-function_value(a,d-h))/(2*h);
    
    if (abs(val_d1 - val_d2) < 0.0001) {
        return val_d2;
    }

    while (abs(val_d1 - val_d2) >= 0.0001) {
         h /= 10.0;

        val_d1 = val_d2;
        val_d2 = (function_value(a, d+h)-function_value(a,d-h))/(2*h);

    }
    cout << cont;
    return val_d2;
}

// derivada aproximada, 
double aproximated_derivative(double a, double d) {
    double h = 0.000001;
    return ((function_value(a, d+h)- function_value(a, d-h))/(2*h));
}
