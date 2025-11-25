#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <vector>
#include <string>

struct MethodResult {

    std::string method_name; 
    
    double final_d; // O valor final de 'd' encontrado (raiz)
    
    double final_error; // O erro associado à última iteração
    
    int total_iterations;    
};

void print_header(); // Exibe o cabeçalho inicial do projeto

void print_separator(); // Exibe uma linha separadora

// Exibe a tabela passo-a-passo de um método específico
// history: vetor contendo todos os valores de 'd' encontrados em cada iteração
void print_iteration_table(const std::string& method_name, const std::vector<double>& history);

void print_comparison_table(const std::vector<MethodResult>& results); // Exibe a tabela final comparando todos os métodos executados

MethodResult create_result(const std::string& name, const std::vector<double>& history); // Converte o histórico bruto de iterações na estrutura MethodResult usada pelas tabelas

void analyze_safety(double d, double a); // Analisa e exibe se o deslocamento é seguro ou crítico (d > 0.7)

#endif