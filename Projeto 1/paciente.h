#ifndef PACIENTE_H
#define PACIENTE_H
#include "pilha.h"

#define TAMANHO_NOME 30

typedef struct Paciente {
    int id;
    char nome[TAMANHO_NOME];
    PILHA* historico;
} Paciente;

#endif 