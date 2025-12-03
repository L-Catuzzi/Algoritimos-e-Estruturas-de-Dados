#ifndef PACIENTE_H
#define PACIENTE_H

#define TAMANHO_NOME 30

typedef struct Paciente {
    int id;
    char nome[TAMANHO_NOME];
} Paciente;

#endif 