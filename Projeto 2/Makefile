# --- Variáveis de Configuração ---
CC = gcc
# Flags: -Wall (avisos), -g (debug), -std=c11 (padrão C atual)
CFLAGS = -Wall -g -std=c11

# Nome do executável final
EXEC = hospital_system

# Lista de arquivos fonte (.c) baseada nas suas imagens
SOURCES = main.c lista.c heap.c io.c 

# Gera a lista de objetos (.o) automaticamente
OBJECTS = $(SOURCES:.c=.o)

# --- Regras Principais ---

# Regra padrão (ao digitar 'make')
all: $(EXEC)

# Linkagem: Cria o executável a partir dos objetos
$(EXEC): $(OBJECTS)
	@echo "Linkando o executavel: $@"
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Compilacao concluida com sucesso!"

# Compilação Genérica: Transforma .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Dependências dos Headers ---
# Garante que se um .h mudar, o .c correspondente recompila

# O main conecta tudo
main.o: main.c lista.h heap.h io.h paciente.h

# Estruturas de Dados
lista.o: lista.c lista.h paciente.h
heap.o: heap.c heap.h paciente.h


# Módulo de Persistência (IO)
# O IO precisa conhecer Lista e Heap para salvar/carregar
io.o: io.c io.h lista.h heap.h paciente.h

# --- Regras de Limpeza ---

.PHONY: clean run

# Limpa arquivos temporários e executável
clean:
	rm -f $(OBJECTS) $(EXEC)
	@echo "Limpeza concluida."

# Compila e roda o programa imediatamente
run: all
	./$(EXEC)