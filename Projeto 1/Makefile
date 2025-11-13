# --- Variáveis de Configuração ---
CC = gcc
CFLAGS = -Wall -g -std=c11

# O nome do arquivo executável que será gerado
EXEC = hospital_ps

# Lista de todos os arquivos de código-fonte (.c) do projeto
SOURCES = main.c lista.c fila.c pilha.c io.c

# Gera automaticamente a lista de arquivos objeto (.o) a partir da lista de fontes
OBJECTS = $(SOURCES:.c=.o)

# --- Regras (Targets) ---

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	# $< significa "a primeira dependência" (o arquivo .c correspondente).
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c lista.h paciente.h fila.h pilha.h io.h
lista.o: lista.c lista.h paciente.h pilha.h           
fila.o: fila.c fila.h paciente.h
pilha.o: pilha.c pilha.h paciente.h lista.h           
io.o: io.c io.h lista.h fila.h pilha.h paciente.h

# --- Regras "Falsas" (Phony Targets) ---

.PHONY: clean

clean:
	rm -f $(EXEC) $(OBJECTS)