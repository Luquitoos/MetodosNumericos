#include <iostream> 
#include <vector>
#include "../include/num_methods.h"
#include "../include/math_utils.h"
#include <cmath>
using namespace std;

// function: f(d) = a*e^d -4d^2
//a = 1
//d = 0.5

void newton_raphson_method(vector<double>* values_d, double a, double d, int max, const double tolerance) {
    values_d->push_back(d);
    double val = values_d->back();
    values_d->push_back(val - function_value(a, val)/derivate(a,val));
    int i = 0;
    while ((max>i)&&(abs(values_d->back() - (*values_d)[values_d->size()- 2]) >= tolerance )) {
        val = values_d->back();
        values_d->push_back(val - function_value(a, val)/derivate(a,val));
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

void secant_method(std::vector<double>& values_d, double a, double d1, double d2, int max_iter, const double tolerance) {
    
    values_d.clear();
    
    double f1 = function_value(a, d1);
    double f2 = function_value(a, d2);

    if (std::abs(f1) < tolerance) {
        values_d.push_back(d1);
        return; 
    }

    values_d.push_back(d1);
    values_d.push_back(d2);

    if (std::abs(f2) < tolerance) {
        return;
    }

    for (int i = 0; i < max_iter; i++) {
        
        if (std::abs(f2 - f1) < 1e-14) {
            std::cerr << "Erro devido a divisão por zero (f1 ~= f2) na iteração " << i << ".\n";
            return; 
        }

        double next = d2 - f2 * ((d2 - d1) / (f2 - f1));
        
        values_d.push_back(next);

        if (std::abs(next - d2) < tolerance) {
            return;
        }
        
        d1 = d2;
        f1 = f2; 
        
        d2 = next;
        f2 = function_value(a, d2); 
        
        if (std::abs(f2) < tolerance) {
            return;
        }
    }
    
    std::cerr << "Convergência não alcançada após " << max_iter << " iterações.\n";
}
