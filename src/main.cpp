#include <iostream>
#include <vector>
#include "num_methods.cpp"
using namespace std;

// function: f(d) = a*e^d -4d^2
//a = 1
//d = 0.5

int main() {
    vector<double> values_d_newton_raphson;
    vector<double> values_d_secant;
    int num_val_a;
    double tolerance = 0.0001;

    newton_raphson_method(&values_d_newton_raphson, 1.0, 0.5, 500, 0.0001);

    cout << values_d_newton_raphson.back();

    secant_method(&values_d_secant, 1.0, 0.5, 1.0, 500, 0.0001);

    cout << values_d_secant.back();


}