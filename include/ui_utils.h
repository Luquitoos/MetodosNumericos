#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <vector>
#include <string>

struct MethodResult {
    // Nome do método
    std::string method_name; 
    
    // O valor final de 'd' encontrado (raiz)
    double final_d;          
    
    // O erro associado à última iteração
    double final_error;      
    
    // Quantas iterações foram necessárias para chegar ao resultado
    int total_iterations;    
};

// Exibe o cabeçalho inicial do projeto
void print_header();

// Exibe uma linha separadora (estética)
void print_separator();

// Exibe a tabela passo-a-passo de um método específico
// history: vetor contendo todos os valores de 'd' encontrados em cada iteração
void print_iteration_table(const std::string& method_name, const std::vector<double>& history);

// Exibe a tabela final comparando todos os métodos executados
void print_comparison_table(const std::vector<MethodResult>& results);

#endif