#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "paciente.h"
#include "lista.h"
#include "heap.h"

// Define o nome do arquivo binário
#define NOME_ARQUIVO "hospital_data.bin"


void salvar_sistema(HEAP* h, LISTA* l) {
    FILE* arq = fopen(NOME_ARQUIVO, "wb"); 
    if (arq == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo de dados!\n");
        return;
    }

    // 1. SALVAR A LISTA (Histórico/Cadastro Geral)
    // Escrevemos quantos pacientes existem na lista
    int qtd_lista = (l != NULL) ? l->tamanho : 0;
    fwrite(&qtd_lista, sizeof(int), 1, arq);

    if (l != NULL) {
        NOLISTA* atual = l->inicio;
        while (atual != NULL) {
            fwrite(&(atual->paciente), sizeof(Paciente), 1, arq);
            atual = atual->proximo;
        }
    }

    // 2. SALVAR O HEAP (Fila de Espera)
    // Escrevemos os metadados do heap
    int cap_heap = (h != NULL) ? h->capacidade_max : 0;
    int qtd_heap = (h != NULL) ? h->tamanho_atual : 0;
    int contador = (h != NULL) ? h->contador_global : 0;

    fwrite(&cap_heap, sizeof(int), 1, arq);
    fwrite(&qtd_heap, sizeof(int), 1, arq);
    fwrite(&contador, sizeof(int), 1, arq);

    if (h != NULL && qtd_heap > 0) {
        // Salvamos o vetor inteiro de uma vez só! 
        // Isso preserva a árvore binária exata como estava na memória
        fwrite(h->vetor, sizeof(ELEMENTO_HEAP), qtd_heap, arq);
    }

    fclose(arq);
    printf("\nDados do sistema salvos com sucesso em '%s'.\n", NOME_ARQUIVO);
}


void carregar_sistema(HEAP** h, LISTA *l) {
    FILE* arq = fopen(NOME_ARQUIVO, "rb"); 
    if (arq == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando sistema vazio.\n");
        // Se não tem arquivo, inicializa o Heap vazio 
        *h = heap_criar(100); // Capacidade padrão se não tiver save
        return;
    }

    // 1. CARREGAR A LISTA
    int qtd_lista;
    fread(&qtd_lista, sizeof(int), 1, arq);

    // Como 'l' já vem criado da main (vazio), apenas inserimos os pacientes
    for (int i = 0; i < qtd_lista; i++) {
        Paciente p;
        fread(&p, sizeof(Paciente), 1, arq);
        inserir_paciente(l, p); // Usa sua função padrão de lista
    }

    // 2. CARREGAR O HEAP
    int cap_heap, qtd_heap, contador;
    fread(&cap_heap, sizeof(int), 1, arq);
    fread(&qtd_heap, sizeof(int), 1, arq);
    fread(&contador, sizeof(int), 1, arq);

    // Recria o heap com a capacidade correta
    *h = heap_criar(cap_heap);
    (*h)->tamanho_atual = qtd_heap;
    (*h)->contador_global = contador;

    if (qtd_heap > 0) {
        // Lê o vetor inteiro de volta para a memória
        fread((*h)->vetor, sizeof(ELEMENTO_HEAP), qtd_heap, arq);
    }

    fclose(arq);
    printf("\nDados carregados! %d pacientes no cadastro, %d na fila de espera.\n", qtd_lista, qtd_heap);
}