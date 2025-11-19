# MetodosNumericos
Implementação em C++ de métodos numéricos

projeto-sismico/
├── bin/                   # Onde ficará o executável compilado
├── obj/                   # Arquivos objetos (.o) intermediários
├── include/               # Cabeçalhos (.h) - Assinaturas das funções
│   ├── math_utils.h       # Declaração das funções matemáticas
│   ├── physics_model.h    # Declaração da função f(d) e f'(d)
│   ├── num_methods.h      # Declaração dos 3 métodos numéricos
│   ├── ui_utils.h         # Declaração de funções de tabela e menu
│   └── types.h            # Estruturas de dados comuns (ex: Resultado)
├── src/                   # Código fonte (.cpp) - Implementações
│   ├── math_utils.cpp     # Implementação de Taylor para e^x, etc.
│   ├── physics_model.cpp  # A equação f(d) = a*e^d - 4d^2
│   ├── num_methods.cpp    # Lógica do Newton, Newton Mod. e Secante
│   ├── ui_utils.cpp       # Lógica de printar tabelas e comparativos
│   └── main.cpp           # Loop principal, leitura de inputs e chamadas
├── Makefile               # Script para compilar tudo automaticamente
└── README.md              # Documentação do projeto
