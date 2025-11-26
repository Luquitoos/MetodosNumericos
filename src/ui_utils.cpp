#include <iomanip> // Para formatar tabelas (setw, setprecision)
#include <iostream> 
#include <cmath>
#include "../include/ui_utils.h"
using namespace std;

// Constantes de formatação para garantir alinhamento entre as funções
const int largura_rotulo = 20;
const int largura_num = 15;
const int precisao = 8;

void print_header() {
    print_separator();
    // Centraliza o título assumindo uma largura de terminal padrão
    cout << setw(60) << right << "ANALISE DE OSCILACAO DE ONDAS SISMICAS" << "\n";
    cout << setw(55) << right << "Sistema de Metodos Numericos" << "\n";
    print_separator();
}

void print_separator() {
    // Imprime uma linha de 80 traços
    cout << string(80, '-') << "\n";
}

void print_iteration_table(const string& method_name, const vector<double>& history) {
    cout << "\nAnalise para o Metodo: " << method_name << "\n";
    print_separator();
    
    // Cabeçalho da Tabela
    cout << left << setw(10) << "Iter (k)" 
         << right << setw(largura_num) << "d_k (Aprox)" 
         << right << setw(largura_num) << "Erro\n";
              
    print_separator();

    // Dados da Tabela
    for (size_t i = 0; i < history.size(); ++i) {
        double current_d = history[i];
        double error = 0.0;

        // O erro é estritamente definido como |x_k - x_{k-1}|
        if (i > 0) {
            error = abs(history[i] - history[i-1]);
        }

        cout << left << setw(10) << i 
             << right << setw(largura_num) 
             << fixed << setprecision(precisao) << current_d;

        if (i == 0) {
            // Sem erro para o chute inicial
            cout << right << setw(largura_num) << "------"; 
        } else {
            // Usa notação científica para o erro
            cout << right << setw(largura_num) << scientific << setprecision(4) << error;
        }
        cout << "\n";
    }
    print_separator();
    cout << "\n";
}

void print_comparison_table(const vector<MethodResult>& results) {
    cout << "\nRESUMO COMPARATIVO DOS RESULTADOS\n";
    print_separator();

    // Cabeçalho da Tabela
    cout << left << setw(largura_rotulo) << "Nome do Metodo"
         << right << setw(largura_num) << "d Final"
         << right << setw(largura_num) << "Erro Final"
         << right << setw(largura_num) << "Iteracoes" << "\n";

    print_separator();

    // Linhas da Tabela
    for (const auto& res : results) {
        cout << left << setw(largura_rotulo) << res.method_name
             << right << setw(largura_num) << fixed << setprecision(precisao) << res.final_d
             << right << setw(largura_num) << scientific << setprecision(4) << res.final_error
             << right << setw(largura_num) << res.total_iterations << "\n";
    }

    print_separator();
}

MethodResult create_result(const string& name, const vector<double>& history) {
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
        res.final_error = abs(history.back() - history[history.size() - 2]);
    } else {
        res.final_error = 0.0;
    }

    return res;
}

void analyze_safety(double d, double a) {
    cout << "Analise para a = " << a << ": Deslocamento Final d = " << d << " m. ";
    if (d > 0.7) {
        cout << "Oscilacao amplificada. Risco de danos graves.\n";
    } else {
        cout << "Deslocamento dentro dos limites operacionais.\n";
    }
}