#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "paciente.h"
#include <string.h>


LISTA* cria_lista(){
    LISTA* nova_lista = (LISTA*) malloc(sizeof(LISTA));

    if (nova_lista == NULL) {
        printf("Erro: Falha ao alocar memória para a lista!\n");
        return NULL; 
    }

    printf("Lista criada com Sucesso!\n");
    nova_lista->inicio = NULL;  
    nova_lista->fim = NULL;     
    nova_lista->tamanho = 0;    

    return nova_lista;
}

NOLISTA *cria_no(){
    NOLISTA *novo_no = (NOLISTA*)malloc(sizeof(NOLISTA));
    if (novo_no == NULL){
        printf("Erro: falha na alocacao do no da lista!\n");
        return NULL;
    }
    else{
        return novo_no;
    }
}


void inserir_paciente(LISTA *lista, Paciente paciente){
    if (lista == NULL){
        printf("Erro ao inserir paciente, lista nao existe!\n");
        return;
    } 

    NOLISTA *novo_no = cria_no();
    novo_no->proximo = NULL;
    novo_no->paciente = paciente;

    if (lista->inicio == NULL) { // CASO 1: A lista está vazia
        novo_no->anterior = NULL;
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else { 
        novo_no->anterior = lista->fim;
        lista->fim->proximo = novo_no;
        lista->fim = novo_no; 
    }


    lista->tamanho ++;
}




Paciente buscar_paciente(LISTA *lista, char nome[]){
    Paciente paciente_nao_encontrado = {-1, "Nao encontrado"}; // Paciente "fantasma" para erro

    if (lista == NULL || lista->inicio == NULL) {
        return paciente_nao_encontrado;
    }

    NOLISTA *aux = lista->inicio;

    while(aux!= NULL){
        if(strcmp(aux->paciente.nome,nome)==0){
            printf("Paciente %s encontrado!\n", aux->paciente.nome);
            return aux->paciente;
        }
        aux = aux->proximo;
    }

    printf("Paciente '%s' nao existe no registro!\n", nome);
    return paciente_nao_encontrado; 

}

Paciente* buscar_paciente_por_id(LISTA* lista, int id) {
    if (lista == NULL || lista->inicio == NULL) {
        return NULL; 
    }

    NOLISTA *aux = lista->inicio;

    while (aux != NULL) {
        if (aux->paciente.id == id) {
            // Encontrou! Retorna o ENDEREÇO do paciente que está dentro do nó.
            return &(aux->paciente);
        }
        aux = aux->proximo;
    }

    return NULL;
}

void printa_paciente(NOLISTA *no){
    printf("Informacoes do paciente:\nnome: %s\nID: %d\n", no->paciente.nome,no->paciente.id);
}


void listar_pacientes(LISTA *lista){
    if (lista == NULL || lista->inicio == NULL) {
        printf("A lista de pacientes está vazia.\n");
        return;
    }

    NOLISTA *aux = lista->inicio;

    printf("\n--- LISTA DE TODOS OS PACIENTES (%d) ---\n", lista->tamanho);
    while (aux != NULL) {
        printa_paciente(aux); 
        aux = aux->proximo;   
    }
}



void destruir_lista(LISTA* lista) {
    if (lista == NULL) return;

    NOLISTA* no_atual = lista->inicio;
    NOLISTA* proximo_no;

    while (no_atual != NULL) {
        proximo_no = no_atual->proximo;

        // Para cada paciente, primeiro destrua seu histórico
        free(no_atual);

        no_atual = proximo_no;
    }

    free(lista);
    printf("Lista de pacientes e todos os historicos foram destruidos.\n");
}

void apagar_paciente_por_id(LISTA* lista, int id) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Erro: Lista vazia ou inexistente.\n");
        return;
    }

    NOLISTA* atual = lista->inicio;
    NOLISTA* anterior = NULL;

    // Busca o nó
    while (atual != NULL && atual->paciente.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se não encontrou
    if (atual == NULL) {
        printf("Erro: Paciente com ID %d nao encontrado na lista.\n", id);
        return;
    }

    // Lógica de remoção da lista encadeada
    if (anterior == NULL) {
        // Removendo o primeiro elemento
        lista->inicio = atual->proximo;
        // Se a lista tinha só 1 elemento, o fim também vira NULL
        if (lista->inicio == NULL) {
            lista->fim = NULL;
        }
    } else {
        // Removendo do meio ou fim
        anterior->proximo = atual->proximo;
        // Se removeu o último, atualiza o ponteiro fim
        if (atual->proximo == NULL) {
            lista->fim = anterior;
        }
    }

    free(atual); 
    lista->tamanho--;
    printf("Sucesso: Paciente removido do cadastro geral.\n");
}