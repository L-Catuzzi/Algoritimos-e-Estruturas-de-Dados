#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "fila.h"
#include "paciente.h"


FILA *criar_fila(int tamanho){
    FILA* nova_fila = (FILA*) malloc(sizeof(FILA));
    if(nova_fila == NULL){
        printf("Erro ao criar a fila!\n");
        return NULL;
    }
    else {
        nova_fila->inicio = NULL;
        nova_fila->fim = NULL;
        nova_fila->tamanho_atual = 0;
        nova_fila->tamanho_max = tamanho;
        printf("Fila de espera com capacidade para %d pacientes criada!\n", tamanho);
    }
    return nova_fila;    
}


bool inserir_paciente_fila(FILA *fila, Paciente paciente){
    
    if (fila_cheia(fila)) {
        printf("ERRO: Fila de espera esta cheia! Nao foi possivel adicionar '%s'.\n", paciente.nome);
        return 0;
    }


    NOFILA* novo_no = (NOFILA*) malloc(sizeof(NOFILA));
    if (novo_no == NULL){
        printf("Erro ao alocar no da fila!\n");
        return 0; 
    } 

    novo_no->Paciente = paciente;
    novo_no->proximo = NULL;

    
    if (fila_vazia(fila)) {
        
        fila->inicio = novo_no;
        fila->fim = novo_no;
    } else {
        // Se já tem gente, o 'proximo' do antigo fim aponta para o novo nó
        fila->fim->proximo = novo_no;
        fila->fim = novo_no;
    }

    fila->tamanho_atual++;
    printf("Paciente '%s' adicionado(a) a fila de espera.\n", paciente.nome);
    return 1; 
}

Paciente remover_paciente_fila(FILA* fila){
    if (fila_vazia(fila)) {
        printf("Erro: Nao ha pacientes na fila de espera.\n");
        Paciente paciente_vazio = {-1, "Vazio"};
        return paciente_vazio;
    }

    // Remove o nó do início
    NOFILA* no_removido = fila->inicio;
    Paciente paciente_atendido = no_removido->Paciente;

    fila->inicio = fila->inicio->proximo;

    // Se, após a remoção, a fila ficar vazia, o fim também deve ser NULL
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(no_removido);
    fila->tamanho_atual--;

    return paciente_atendido;    
}

void destruir_fila(FILA* fila) {
    while (!fila_vazia(fila)) {
        remover_paciente_fila(fila);
    }
    free(fila);
}

bool fila_vazia(FILA *fila){
    return (fila->tamanho_atual == 0);
}
bool fila_cheia(FILA *fila){
    return (fila->tamanho_atual == fila->tamanho_max);
}

void mostrar_fila_espera(FILA* fila){
    if (fila_vazia(fila)) {
        printf("\n>>> Fila de Espera esta vazia. <<<\n\n");
        return;
    }

    NOFILA* aux = fila->inicio;
    printf("\n--- FILA DE ESPERA ATUAL (%d/%d) ---\n", fila->tamanho_atual, fila->tamanho_max);
    int pos = 1;
    while (aux != NULL) {
        printf("%dº -> ID: %d, Nome: %s\n", pos, aux->Paciente.id, aux->Paciente.nome);
        aux = aux->proximo;
        pos++;
    }
    printf("--- FIM DA FILA ---\n");
}

bool buscar_paciente_na_fila(FILA* fila, int id) {
    if (fila_vazia(fila)) {
        return false;
    }

    NOFILA* aux = fila->inicio;
    while (aux != NULL) {
        if (aux->Paciente.id == id) {
            return true; 
        }
        aux = aux->proximo;
    }

    return false; 
}