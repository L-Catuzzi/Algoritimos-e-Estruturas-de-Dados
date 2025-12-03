#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "paciente.h"
#include <string.h>




/**
 * @brief Aloca memória e inicializa uma nova lista vazia.
 * * A função aloca dinamicamente uma estrutura Lista e configura
 * seus ponteiros 'inicio' e 'fim' como NULL e seu 'tamanho' como 0,
 * @return Um ponteiro (Lista*) para a lista recém-criada, ou NULL se a 
 * alocação de memória falhar.
 */
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




/**
 * @brief 
 * @return Um ponteiro (Paciente*) para o paciente que tiver o nome
 * da busca, ou uma mensagem de erro caso não haja esse paciente
 */
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

/**
 * @brief Percorre toda a lista do começo ao fim, prinando
 * as informações de todos os pacientes
 */
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


/**
 * @brief Realiza a busca do paciente a partir do nome
 * e exclui ele da lista de pacientes
*/
 
void apagar_paciente(LISTA* lista, int id) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Nao e possivel apagar: a lista esta vazia.\n");
        return;
    }

    NOLISTA *no_para_apagar = lista->inicio;

    // Encontra o nó a ser apagado pelo ID
    while (no_para_apagar != NULL && no_para_apagar->paciente.id != id) {
        no_para_apagar = no_para_apagar->proximo;
    }

    if (no_para_apagar == NULL) {
        printf("ERRO: Paciente com ID %d nao encontrado para apagar.\n", id);
        return;
    }

    if (no_para_apagar->anterior != NULL) {
        no_para_apagar->anterior->proximo = no_para_apagar->proximo;
    } else {
        lista->inicio = no_para_apagar->proximo;
    }
    if (no_para_apagar->proximo != NULL) {
        no_para_apagar->proximo->anterior = no_para_apagar->anterior;
    } else {
        lista->fim = no_para_apagar->anterior;
    }

    // Limpeza de memória (histórico e depois o nó)
    printf("Apagando registro e historico do paciente '%s'...\n", no_para_apagar->paciente.nome);
    destruir_pilha(no_para_apagar->paciente.historico);
    free(no_para_apagar); 
    lista->tamanho--;     

    printf("Registro do paciente com ID %d apagado com sucesso.\n", id);
}

void destruir_lista(LISTA* lista) {
    if (lista == NULL) return;

    NOLISTA* no_atual = lista->inicio;
    NOLISTA* proximo_no;

    while (no_atual != NULL) {
        proximo_no = no_atual->proximo;

        // Para cada paciente, primeiro destrua seu histórico
        destruir_pilha(no_atual->paciente.historico);
        
        free(no_atual);

        no_atual = proximo_no;
    }

    free(lista);
    printf("Lista de pacientes e todos os historicos foram destruidos.\n");
}