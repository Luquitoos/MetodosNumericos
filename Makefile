# 1. Configurações do Compilador
CXX      := g++
CXXFLAGS := -Wall -Wextra -g -Iinclude

# 2. Diretórios
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Nome do executável final
TARGET := $(BIN_DIR)/sismico_solver

all: directories $(TARGET)
	@echo "Compilação concluída com sucesso! Execute: ./$(TARGET)"

# Regra para Linkar (Juntar todos os .o e criar o executável)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para Compilar (Transformar cada .cpp em .o individualmente)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para criar as pastas bin e obj se elas não existirem
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Regra de Limpeza (remove arquivos gerados)
clean:
	@echo "Limpando arquivos compilados..."
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Regra para rodar o programa direto
run: all
	@echo "Executando o programa..."
	./$(TARGET)

# Marca estas regras como "não arquivos"
.PHONY: all clean run directories