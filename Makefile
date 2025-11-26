# 1. Configurações do Compilador
CXX      := g++
# -MMD e -MP geram arquivos .d que mapeiam as dependências dos headers
CXXFLAGS := -Wall -Wextra -g -Iinclude -MMD -MP

# 2. Diretórios
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# 3. Arquivos
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
# Lista de arquivos de dependência (.d) gerados automaticamente
DEPS := $(OBJS:.o=.d)

# Nome do executável final
TARGET := $(BIN_DIR)/sismico_solver

all: directories $(TARGET)
	@echo "Compilação concluída! Execute: ./$(TARGET)"

# Linkagem
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Inclui as regras de dependência geradas pelo compilador (se existirem)
-include $(DEPS)

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

clean:
	@echo "Limpando arquivos..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	@echo "Executando..."
	./$(TARGET)

.PHONY: all clean run directories