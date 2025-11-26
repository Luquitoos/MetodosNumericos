#include <iostream> 
#include <vector>
#include "../include/num_methods.h"
#include "../include/math_utils.h"
#include <cmath>
using namespace std;

// função: f(d) = a*e^d -4d^2
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
        cout << "O resultado não converge com esse limite de iteração.\n";
    }
}

void newton_modified_method(std::vector<double>* values_d, double a, double d, int max, const double tolerance) {
    values_d->push_back(d); 
    double deriv_const = derivate(a, d);
    
    if (std::abs(deriv_const) < 1e-14) {
        std::cerr << "Erro: Derivada inicial muito proxima de zero.\n";
        return;
    }

    int i = 0;
    while (i < max) {
        double current_val = values_d->back();
        double f_val = function_value(a, current_val);
        double next_val = current_val - (f_val / deriv_const);
        values_d->push_back(next_val);
        
        if (std::abs(next_val - current_val) < tolerance) {
            return;
        }
        
        i++;
    }
    
    std::cout << "Aviso: O metodo Newton Modificado nao convergiu apos " << max << " iteracoes.\n";
}

void secant_method(std::vector<double>* values_d, double a, double d1, double d2, int max, const double tolerance) {
    
    if (values_d == nullptr) {
        cerr << "Erro: Ponteiro para vetor nulo.\n";
        return;
    }

    values_d->clear();
    
    double f1 = function_value(a, d1);
    double f2 = function_value(a, d2);

    if (abs(f1) < tolerance) {
        values_d->push_back(d1);
        return; 
    }

    values_d->push_back(d1);
    values_d->push_back(d2);

    if (abs(f2) < tolerance) {
        return;
    }

    for (int i = 0; i < max; i++) {
        
        if (abs(f2 - f1) < 1e-14) {
            cerr << "Erro devido a divisão por zero (f1 ~= f2) na iteração " << i << ".\n";
            return; 
        }

        double next = d2 - f2 * ((d2 - d1) / (f2 - f1));
        
        values_d->push_back(next);

        if (abs(next - d2) < tolerance) {
            return;
        }
        
        d1 = d2;
        f1 = f2; 
        
        d2 = next;
        f2 = function_value(a, d2); 
        
        if (abs(f2) < tolerance) {
            return;
        }
    }
    
    cerr << "Convergência não alcançada após " << max << " iterações.\n";
}
