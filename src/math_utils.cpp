#include <iostream>
#include "../include/math_utils.h"
#include <cmath>
#include <string>
using namespace std;

double function_value(double a, double d) {
    return ((a * exp(d)) - (4 * pow(d, 2)));
}

double derivate(double a, double x) {
    // 6.0e-6 é um bom valor por estar alinhado com o "machine epsilon", vai reduzir problemas de truncamento
    double h = 6.0e-6 * fmax(abs(x), 1.0);

    double f_soma = function_value(a, x + h);
    double f_sub = function_value(a, x - h);

    return (f_soma - f_sub) / (2.0 * h);
}
