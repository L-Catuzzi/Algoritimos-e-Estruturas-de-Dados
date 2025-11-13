#ifndef PILHA_H
    #define PILHA_H
    #include "paciente.h"
    #include <stdbool.h>
    #define MAX_PROCEDIMENTOS 10
    #define TAMANHO_PROCEDIMENTO 101

    struct lista_;
    typedef struct lista_ LISTA;

    typedef struct no_p NOPILHA;

    typedef struct pilha_ PILHA;
    struct no_p {
        char procedimento[TAMANHO_PROCEDIMENTO];
        NOPILHA* proximo;
    };

    struct pilha_ {
        NOPILHA* topo;
        int tamanho_atual;
        int tamanho_maximo;
    };


void adicionar_procedimento(LISTA* lista_pacientes, int id_paciente, const char* procedimento);
void desfazer_procedimento(LISTA* lista_pacientes, int id_paciente);



PILHA* criar_pilha();
int pilha_push(PILHA* pilha, const char* procedimento);
char* pilha_pop(PILHA* pilha, char* buffer_saida);
bool historico_vazio(PILHA* pilha);
bool historico_cheio(PILHA* pilha);
const char* consultar_procedimento(PILHA* pilha);
void mostrar_historico(PILHA* pilha);
void destruir_pilha(PILHA* pilha);



#endif