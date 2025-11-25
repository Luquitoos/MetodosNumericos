#include <iomanip> // Para formatar tabelas (setw, setprecision)
#include <iostream> 
#include <cmath>
#include "../include/ui_utils.h"

// Constantes de formatação para garantir alinhamento entre as funções
const int largura_rotulo = 20;
const int largura_num = 15;
const int precisao = 8;

void print_header() {
    print_separator();
    // Centraliza o título assumindo uma largura de terminal padrão
    std::cout << std::setw(60) << std::right << "ANALISE DE OSCILACAO DE ONDAS SISMICAS" << "\n";
    std::cout << std::setw(55) << std::right << "Sistema de Metodos Numericos" << "\n";
    print_separator();
}

void print_separator() {
    // Imprime uma linha de 80 traços
    std::cout << std::string(80, '-') << "\n";
}

void print_iteration_table(const std::string& method_name, const std::vector<double>& history) {
    std::cout << "\nAnalise para o Metodo: " << method_name << "\n";
    print_separator();
    
    // Cabeçalho da Tabela
    std::cout << std::left << std::setw(10) << "Iter (k)" 
              << std::right << std::setw(largura_num) << "d_k (Aprox)" 
              << std::right << std::setw(largura_num) << "Erro\n";
              
    print_separator();

    // Dados da Tabela
    for (size_t i = 0; i < history.size(); ++i) {
        double current_d = history[i];
        double error = 0.0;

        // calcula a subtração entre o passo atual e o anterior apenas para exibir na coluna "Error"
        // O erro é estritamente definido como |x_k - x_{k-1}|
        if (i > 0) {
            error = std::abs(history[i] - history[i-1]);
        }

        std::cout << std::left << std::setw(10) << i 
                  << std::right << std::setw(largura_num) 
                  << std::fixed << std::setprecision(precisao) << current_d;

        if (i == 0) {
            // Sem erro para o chute inicial
            std::cout << std::right << std::setw(largura_num) << "------"; 
        } else {
            // Usa notação científica para o erro
            std::cout << std::right << std::setw(largura_num) << std::scientific << std::setprecision(4) << error;
        }
        std::cout << "\n";
    }
    print_separator();
    std::cout << "\n";
}

void print_comparison_table(const std::vector<MethodResult>& results) {
    std::cout << "\nRESUMO COMPARATIVO DOS RESULTADOS\n";
    print_separator();

    // Cabeçalho da Tabela
    std::cout << std::left << std::setw(largura_rotulo) << "Nome do Metodo"
              << std::right << std::setw(largura_num) << "d Final"
              << std::right << std::setw(largura_num) << "Erro Final"
              << std::right << std::setw(largura_num) << "Iteracoes" << "\n";

    print_separator();

    // Linhas da Tabela
    for (const auto& res : results) {
        std::cout << std::left << std::setw(largura_rotulo) << res.method_name
                  << std::right << std::setw(largura_num) << std::fixed << std::setprecision(precisao) << res.final_d
                  << std::right << std::setw(largura_num) << std::scientific << std::setprecision(4) << res.final_error
                  << std::right << std::setw(largura_num) << res.total_iterations << "\n";
    }

    print_separator();
}

MethodResult create_result(const std::string& name, const std::vector<double>& history) {
    MethodResult res;
    res.method_name = name;
    
    if (history.empty()) {
        res.final_d = 0.0;
        res.final_error = 0.0;
        res.total_iterations = 0;
        return res;
    }

    res.final_d = history.back();
    res.total_iterations = (int)history.size() - 1; // Desconta o chute inicial

    // Erro aproximado: |x_k - x_{k-1}|
    if (history.size() >= 2) {
        res.final_error = std::abs(history.back() - history[history.size() - 2]);
    } else {
        res.final_error = 0.0;
    }

    return res;
}

void analyze_safety(double d, double a) {
    std::cout << "Analise para a = " << a << ": Deslocamento Final d = " << d << " m. ";
    if (d > 0.7) {
        std::cout << "Oscilacao amplificada. Risco de danos graves.\n";
    } else {
        std::cout << "Deslocamento dentro dos limites operacionais.\n";
    }
}