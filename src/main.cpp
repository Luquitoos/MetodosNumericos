#include <iostream>
#include <vector>
#include <string>
#include "../include/num_methods.h"
#include "../include/ui_utils.h"
#include "../include/math_utils.h"
using namespace std;

const double d0 = 0.5;        // Chute inicial
const double d1 = 0.4;        // Segundo ponto (Secante: d0 - 0.1) Qualquer coisa a gente vai mudando
const int max_iter = 100;     // Limite de segurança

int main() {
    print_header();

    std::vector<double> a_values;
    
    int n;
    double epsilon;

    // Inserir número de valores de a
    std::cout << "Insira o numero de valores para 'a' (n): ";
    std::cin >> n;

    // Inserir a (para cada n)
    std::cout << "Insira os " << n << " valores para a amplitude 'a':\n";
    for (int i = 0; i < n; ++i) {
        double val;
        
        std::cout << "Valor " << (i + 1) << ": ";
        std::cin >> val;
        
        a_values.push_back(val);
    }

    // Inserir Precisão
    std::cout << "Insira a precisao (epsilon): ";
    std::cin >> epsilon;

    // Loop do Menu
    int choice; 
    do {
        cout << "\n=== MENU DE METODOS NUMERICOS ===\n";
        cout << "1. Metodo de Newton-Raphson\n";
        cout << "2. Metodo de Newton Modificado\n";
        cout << "3. Metodo da Secante\n";
        cout << "4. Executar TODOS e Comparar\n";
        cout << "0. Sair\n";
        cout << "Selecione uma opcao: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Encerrando o sistema...\n";
            break; 
        }

        if (choice < 1 || choice > 4) {
            cout << "Opcao invalida. Tente novamente.\n";
            continue;
        }

        switch (choice) {
            case 1: { // Newton-Raphson
                for (double a : a_values) {
                    vector<double> history;
                    string label = "Newton-Raphson (a=" + to_string(a).substr(0, 4) + ")";
                    
                    newton_raphson_method(&history, a, d0, max_iter, epsilon);
                    print_iteration_table(label, history);
                    analyze_safety(history.back(), a);
                }
                break;
            }

            case 2: { // Newton Modificado
                for (double a : a_values) {
                    vector<double> history;
                    string label = "Newton Mod (a=" + to_string(a).substr(0, 4) + ")";
                    
                    newton_modified_method(&history, a, d0, max_iter, epsilon);
                    print_iteration_table(label, history);
                    analyze_safety(history.back(), a);
                }
                break;
            }

            case 3: { // Secante
                for (double a : a_values) {
                    vector<double> history;
                    string label = "Secante (a=" + to_string(a).substr(0, 4) + ")";
                    
                    secant_method(&history, a, d1, d0, max_iter, epsilon);
                    print_iteration_table(label, history);
                    analyze_safety(history.back(), a);
                }
                break;
            }

            case 4: { // Comparativo Geral
                vector<MethodResult> comparative_results;
                
                // Loop para calcular tudo antes de mostrar
                for (double a : a_values) {
                    vector<double> h_newton, h_mod, h_sec;
                    string suffix = " (a=" + to_string(a).substr(0, 4) + ")";
                    
                    // Executa Newton
                    newton_raphson_method(&h_newton, a, d0, max_iter, epsilon);
                    comparative_results.push_back(create_result("Newton" + suffix, h_newton));

                    // Executa Newton Modificado
                    newton_modified_method(&h_mod, a, d0, max_iter, epsilon);
                    comparative_results.push_back(create_result("Newton Mod" + suffix, h_mod));

                    // Executa Secante
                    secant_method(&h_sec, a, d1, d0, max_iter, epsilon);
                    comparative_results.push_back(create_result("Secante" + suffix, h_sec));
                }

                // Exibe a Tabela Unificada
                print_comparison_table(comparative_results);
                
                // Análise de risco percorrendo para cada resultado em resultados
                cout << "\nVerificando deslocamentos criticos (d > 0.7)...\n";
                bool risk_found = false;
                
                for(const auto& res : comparative_results) {
                    
                    if(res.final_d > 0.7) {
                        cout << " -> ALERTA: " << res.method_name << " atingiu d = " << res.final_d << " (RISCO)\n";
                        risk_found = true;
                    }

                }
                
                if (!risk_found) cout << "Nenhum risco critico detectado\n";
                
                break;
            }
        }

    } while (choice != 0);

    std::cout << "Sistema encerrando.\n";
    return 0;
}