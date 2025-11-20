#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

// that function calculates the derivative of f(d) = a*e^d - 4d^2 at d
double derivate_function (double a, double d) {
    double h = 0.1;
    int i = 0;
    vector<double> valores;

    valores.push_back(d);
    valores.push_back(((a*exp(d+h)-4*pow(d+h, 2))-(a*exp(d)-4*pow(d, 2)))/h);

    while (abs(valores[i]-valores[i+1]) >= 0.00001) {
        i++;
        h /= 10.0;
        valores.push_back(((a*exp(d+h)-4*pow(d+h, 2))-(a*exp(d)-4*pow(d, 2)))/h);
    }

    return valores[i+1];
}

// and that calculates the normal function value
double function_value(double a, double d) {
    return exp(d) - 4 * pow(d, 2);
}




