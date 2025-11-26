# Análise de Oscilação de Ondas Sísmicas - Solucionador Numérico

Este projeto implementa um sistema em C++ para encontrar as raízes da função de oscilação de ondas sísmicas. O software foi desenvolvido para analisar o comportamento de ondas sob diferentes amplitudes e verificar riscos estruturais baseados em limites de deslocamento.

---

## Sumário
1. [Descrição do Problema](#-descrição-do-problema)
2. [Estrutura do Projeto](#-estrutura-do-projeto)
3. [Fundamentação Teórica e Implementação](#-fundamentação-teórica-e-implementação)
    - [Derivada Numérica (Escolha do h)](#1-derivada-numérica)
    - [Método de Newton-Raphson](#2-método-de-newton-raphson)
    - [Método de Newton Modificado](#3-método-de-newton-modificado)
    - [Método da Secante](#4-método-da-secante)
4. [Guia de Uso e Exemplos](#-guia-de-uso-e-exemplos)
5. [Infraestrutura, Compilação e Execução](#-infraestrutura-compilação-e-execução)

---

## Descrição do Problema

As oscilações causadas por ondas sísmicas neste modelo são regidas pela função não-linear:

$$f(d) = a \cdot e^d - 4d^2$$

**Variáveis:**
* **$d$**: Deslocamento da onda (a raiz que buscamos, onde $f(d) = 0$).
* **$a$**: Amplitude da oscilação (parâmetro de entrada variável).

**Critério de Segurança:**
Se a raiz encontrada for **$d > 0.7$ m**, a oscilação é classificada como **CRÍTICA** (amplificada), indicando risco de danos graves.

---

## Estrutura do Projeto

```text
/
├── bin/                 # Executáveis gerados
├── include/             # Arquivos de Cabeçalho (.h)
│   ├── math_utils.h     # Declarações matemáticas
│   ├── num_methods.h    # Declarações dos métodos numéricos
│   └── ui_utils.h       # Declarações de interface UI
├── obj/                 # Objetos de compilação (.o)
├── src/                 # Código Fonte (.cpp)
│   ├── main.cpp         # Menu e orquestração
│   ├── math_utils.cpp   # Implementação da Derivada e Função
│   ├── num_methods.cpp  # Implementação Lógica dos Algoritmos
│   └── ui_utils.cpp     # Tabelas e formatação
├── Makefile             # Automação de compilação
├── Dockerfile           # Imagem Linux/GCC
└── docker-compose.yml   # Orquestração Windows
```

---

## Fundamentação Teórica e Implementação

Abaixo detalhamos a matemática de cada método seguida de sua implementação prática no código.

### 1. Derivada Numérica

**Fundamentação Teórica:**
Utilizamos a **Diferença Central** para aproximar a derivada:
$$f'(x) \approx \frac{f(x+h) - f(x-h)}{2h}$$

**A Escolha Ótima do Passo $h$:**
A escolha de $h$ é um problema de otimização.
1.  Se $h$ for muito grande, o **Erro de Truncamento** (da Série de Taylor) é alto.
2.  Se $h$ for muito pequeno, o **Erro de Arredondamento** (devido à precisão finita do computador) domina, causando cancelamento catastrófico.

O ponto ótimo ocorre quando esses dois erros se equilibram, sendo proporcional à raiz cúbica do Epsilon da Máquina ($\epsilon_{mach}$):

$$
h_{otimo} \approx \sqrt[3]{\epsilon_{mach}} \cdot x
$$

Para variáveis de dupla precisão (`double` em C++), $\epsilon_{mach} \approx 2.2 \times 10^{-16}$. 

Calculando a raiz cúbica:

$$
\sqrt[3]{2.2 \times 10^{-16}} \approx 6.0 \times 10^{-6}
$$

Portanto, para garantir estabilidade numérica em qualquer escala de $d$, utilizamos a fórmula:

$$ 
h = 6 \times 10^{-6} \cdot \max(|d|, 1) 
$$

**Implementação (`math_utils.cpp`):**

```cpp
double derivate(double a, double x) {
    // Aplicação da fórmula baseada no epsilon machine
    double h = 6.0e-6 * fmax(abs(x), 1.0);

    double f_soma = function_value(a, x + h);
    double f_sub = function_value(a, x - h);

    return (f_soma - f_sub) / (2.0 * h);
}
```

---

### 2. Método de Newton-Raphson

**Fundamentação Teórica:**
É um método iterativo de convergência quadrática (rápida). Ele utiliza a reta tangente ao ponto $x_k$ para estimar onde a função cruza o eixo zero.

A fórmula de iteração é:

$$ 
x_{k+1} = x_k - \frac{f(x_k)}{f'(x_k)} 
$$

**Implementação (`num_methods.cpp`):**
Note que a função `derivate` é chamada dentro do loop `while`, ou seja, a inclinação da tangente é recalculada a cada passo com a precisão definida acima.

```cpp
void newton_raphson_method(vector<double>* values_d, double a, double d, int max, const double tolerance) {
    values_d->push_back(d); // Histórico x0
    
    // Primeiro passo
    double val = values_d->back();
    double next_val = val - function_value(a, val) / derivate(a, val);
    values_d->push_back(next_val);

    int i = 0;
    // Loop continua enquanto erro > tolerancia
    while ((max > i) && (abs(values_d->back() - (*values_d)[values_d->size()- 2]) >= tolerance )) {
        val = values_d->back();
        // FÓRMULA: x_new = x_old - f(x)/f'(x)
        next_val = val - function_value(a, val) / derivate(a, val);
        values_d->push_back(next_val);
        i++;
    }
}
```

---

### 3. Método de Newton Modificado

**Fundamentação Teórica:**
Para evitar o custo computacional de calcular a derivada $f'(x_k)$ em toda iteração (o que pode ser custoso em funções complexas), este método calcula a derivada **apenas no ponto inicial** $x_0$ e a mantém constante.

A fórmula de iteração torna-se:

$$ 
x_{k+1} = x_k - \frac{f(x_k)}{f'(x_0)} 
$$

A convergência torna-se linear (mais lenta), mas o custo por passo diminui.

**Implementação (`num_methods.cpp`):**
Observe que `deriv_const` é calculada fora do laço `for`.

```cpp
void newton_modified_method(vector<double>* values_d, double a, double d, int max, const double tolerance) {
    values_d->clear();
    values_d->push_back(d); 
    
    // CÁLCULO ÚNICO DA DERIVADA (f'(x0))
    double deriv_const = derivate(a, d);
    
    for (int i = 0; i < max; ++i) {
        double current_val = values_d->back();
        double f_val = function_value(a, current_val);
        
        // Usa a constante no denominador
        double next_val = current_val - (f_val / deriv_const);
        values_d->push_back(next_val);
        
        if (abs(next_val - current_val) < tolerance) return;
    }
}
```

---

### 4. Método da Secante

**Fundamentação Teórica:**
O método da Secante substitui a necessidade da derivada analítica ou numérica aproximando a tangente por uma reta secante que passa pelos dois últimos pontos calculados ($x_k$ e $x_{k-1}$).

A fórmula de iteração é:

$$ 
x_{k+1} = x_k - f(x_k) \cdot \frac{x_k - x_{k-1}}{f(x_k) - f(x_{k-1})} 
$$

Isso requer dois chutes iniciais ($d_0$ e $d_1$).

**Implementação (`num_methods.cpp`):**
O código gerencia a atualização das variáveis `d1` (anterior) e `d2` (atual) a cada iteração.

```cpp
void secant_method(vector<double>* values_d, double a, double d1, double d2, int max, const double tolerance) {
    values_d->clear();
    // Armazena os dois chutes iniciais no histórico
    values_d->push_back(d1);
    values_d->push_back(d2);

    for (int i = 0; i < max; i++) {
        double f1 = function_value(a, d1);
        double f2 = function_value(a, d2);
        
        // Proteção contra divisão por zero
        if (abs(f2 - f1) < 1e-14) return; 

        // FÓRMULA DA SECANTE
        double next = d2 - f2 * ((d2 - d1) / (f2 - f1));
        
        values_d->push_back(next);

        if (abs(next - d2) < tolerance) return;
        
        // Atualiza ("shift") os pontos
        d1 = d2;
        d2 = next;
    }
}
```

---

## Guia de Uso e Exemplos

Ao iniciar, o sistema solicita:

n   → quantidade de valores de a
a_i → cada amplitude
ε   → tolerância

Depois exibe o menu:

1. Metodo de Newton-Raphson
2. Metodo de Newton Modificado
3. Metodo da Secante
4. Executar TODOS e Comparar
0. Sair

Ao rodar o sistema, você verá o seguinte comportamento para cada opção do menu.

### Opção 1: Newton-Raphson
Ideal para convergência rápida.

```text
Exemplo — Newton–Raphson (a = 1)

Analise para o Metodo: Newton-Raphson (a=1.0000)
--------------------------------------------------------------------------------
Iter (k)         d_k (Aprox)             Erro
--------------------------------------------------------------------------------
0                0.50000000              ------
1                0.43848123        6.1512e-02
2                0.43701587        1.4654e-03
3                0.43700743        8.4362e-06
4                0.43700737        5.8300e-08
--------------------------------------------------------------------------------

Analise para a = 1: Deslocamento Final d = 0.43700737 m.
Deslocamento dentro dos limites operacionais.
```

### Opção 2: Newton Modificado
Note que ele leva mais iterações (k=5) que o Newton padrão para a mesma precisão, pois a derivada é fixa.

```text
Exemplo — Newton Modificado (a = 1)

Analise para o Metodo: Newton Mod (a=1.0000)
--------------------------------------------------------------------------------
Iter (k)         d_k (Aprox)             Erro
--------------------------------------------------------------------------------
0                0.50000000              ------
1                0.43842365        6.1576e-02
2                0.43704188        1.3818e-03
3                0.43700865        3.3235e-05
4                0.43700740        1.2461e-06
5                0.43700737        3.7700e-08
--------------------------------------------------------------------------------

Convergência mais lenta, mas resultado final idêntico.
```

### Opção 4: Quadro Comparativo
Exibe o resumo de todos os métodos executados.

```text
Comparação — Múltiplos Métodos

RESUMO COMPARATIVO DOS RESULTADOS
--------------------------------------------------------------------------------
Metodo                 d Final         Erro Final        Iteracoes
--------------------------------------------------------------------------------
Newton (a=1.0)         0.43700737      5.8300e-08         4
Newton Mod (a=1.0)     0.43700737      3.7700e-08         5
Secante (a=1.0)        0.43700737      3.4700e-07         5
--------------------------------------------------------------------------------

Verificando deslocamentos criticos (d > 0.7)...
Nenhum risco critico detectado
```

---

## Infraestrutura, Compilação e Execução

Este projeto utiliza um `Makefile` para gerenciar a compilação. Abaixo estão as instruções para diferentes ambientes.

### Como Rodar o Executável

Após a compilação (seja via `make` nativo ou Docker), o executável binário é gerado dentro da pasta `bin/`.

**Comando para executar:**
```bash
./bin/sismico_solver
```

---

### Windows (Via Docker Compose - Recomendado)
Garante compatibilidade total evitando erros de ambiente.

1.  **Compilar e Rodar (Automático):**
    ```powershell
    docker-compose up
    ```
    *Este comando cria o container, compila o código e executa o binário automaticamente.*

2.  **Ambiente de Desenvolvimento (Interativo):**
    Para acessar o terminal Linux:
    ```powershell
    docker-compose run --rm app /bin/bash
    ```
    *Dentro do container:*
    1.  `make` (Para compilar)
    2.  `./bin/sismico_solver` (Para rodar o executável)

### Linux / WSL (Nativo)

1.  **Compilar:**
    No terminal, na raiz do projeto:
    ```bash
    make
    ```

2.  **Rodar:**
    ```bash
    ./bin/sismico_solver
    # Ou use o atalho do Makefile:
    make run
    ```

3.  **Limpar Arquivos:**
    Para remover os arquivos `.o` e o executável:
    ```bash
    make clean
    ```