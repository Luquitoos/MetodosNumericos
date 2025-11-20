#include <iostream>
//#include <vector>
#include <cmath>
#include <string>
using namespace std;

// that function calculates the derivative of f(d) = a*e^d - 4d^2 at d

double function_value(double a, double d) {
    return ((a * exp(d)) - (4 * pow(d, 2)));
}

/*

that fun calculates the derivative, but it's using momory a lot, 'cause I was using vectors

double derivate_function (double a, double d) {
    double h = 0.1;
    int i = 0;
    vector<double> valores;

    valores.push_back(d);
    valores.push_back((function_value(a, d+h)-function_value(a,d))/h);

    while (abs(valores[i]-valores[i+1]) >= 0.00001) {
        i++;
        h /= 10.0;
        valores.push_back((function_value(a, d+h)-function_value(a,d))/h);
    }

    return valores[i+1];
}
*/

double derivate(double a, double d) {
    
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

    return val_d2;
}

// and that calculates the normal function value





