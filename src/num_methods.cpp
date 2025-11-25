#include <iostream> 
#include <vector>
#include "../include/num_methods.h"
#include "../include/math_utils.h"
#include <cmath>
using namespace std;

// function: f(d) = a*e^d -4d^2
//a = 1
//d = 0.5

// o valor do topo do vetor é o valor final calculado pelo método
void newton_raphson_method(vector<double>* values_d, double a, double d, int max, const double tolerance) {
    values_d->push_back(d);
    double val = values_d->back();
    double derivative = derivate(a,val);
    if (first_derivative == 0) {
        cerr << "a derivada da função retornou um valor nulo";
    values_d->push_back(val - function_value(a, val)/derivative);
    int i = 1; // o contador começa em 1 pq eu já gastei poder computacional na linha 15
    while ((max>i)&&(abs(values_d->back() - (*values_d)[values_d->size()- 2]) >= tolerance )) {
        val = values_d->back();
        derivative = derivate(a,val);
        if (derivative == 0) {
            cerr << "A derivada da função retornou um valor nulo";
            break;
        values_d->push_back(val - function_value(a, val)/derivative);
        i++;
    }
    if (i >= max) {
        cerr << "The result doesn't converge with that interation limit\n";
    }
}

// the difference between newton-raphson and newton modified is just the derivate, the cost of this algorithm is shorter 'cause derivate only one time
void newton_modified_method(vector<double>* values_d, double a, double d, int max, const double tolerance) {
    values_d->push_back(d);
    double val = values_d->back();
    double static_derivative = derivate(a,val);
    if (static_derivate == 0) {
        cerr << "A derivada dessa função é igual a 0";
    }
    values_d->push_back(val - function_value(a, val)/static_derivative);
    int i = 0;
    while ((max>i)&&(abs(values_d->back() - (*values_d)[values_d->size()- 2]) >= tolerance )) {
        val = values_d->back();
        values_d->push_back(val - function_value(a, val)/static_derivative);
        i++;
    }
    if (i >= max) {
        cerr << "The result doesn't converge with that interation limit\n";
    }
}

void secant_method(vector<double>& values_d, double a, double d1, double d2, int max_iter, const double tolerance) {
    
    values_d.clear();
    
    double f1 = function_value(a, d1);
    double f2 = function_value(a, d2);

    if (abs(f1) < tolerance) {
        values_d.push_back(d1);
        return; 
    }

    values_d.push_back(d1);
    values_d.push_back(d2);

    if (abs(f2) < tolerance) {
        return;
    }

    for (int i = 0; i < max_iter; i++) {
        
        if (abs(f2 - f1) < 1e-14) {
            cerr << "Erro devido a divisão por zero (f1 ~= f2) na iteração " << i << ".\n";
            return; 
        }

        double next = d2 - f2 * ((d2 - d1) / (f2 - f1));
        
        values_d.push_back(next);

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
    
    cerr << "Convergência não alcançada após " << max_iter << " iterações.\n";
}
