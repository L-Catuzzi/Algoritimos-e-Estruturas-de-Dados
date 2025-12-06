#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


static bool eh_mais_prioritario(ELEMENTO_HEAP a, ELEMENTO_HEAP b) {
    // 1. Critério: Menor número de prioridade ganha (1 é maior que 5)
    if (a.prioridade < b.prioridade) return true;
    if (a.prioridade > b.prioridade) return false;
    
    // 2. Critério (Empate): Menor ordem de chegada ganha (quem chegou antes)
    return a.ordem_chegada < b.ordem_chegada;
}

static void troca(ELEMENTO_HEAP* a, ELEMENTO_HEAP* b) {
    ELEMENTO_HEAP temp = *a;
    *a = *b;
    *b = temp;
}

static void sobe_heap(HEAP* h, int indice) {
    if (indice == 0) return;
    int pai = (indice - 1) / 2;

    if (eh_mais_prioritario(h->vetor[indice], h->vetor[pai])) {
        troca(&h->vetor[indice], &h->vetor[pai]);
        sobe_heap(h, pai);
    }
}

static void desce_heap(HEAP* h, int indice) {
    int esq = 2 * indice + 1;
    int dir = 2 * indice + 2;
    int maior_prio = indice;

    if (esq < h->tamanho_atual && eh_mais_prioritario(h->vetor[esq], h->vetor[maior_prio])) {
        maior_prio = esq;
    }
    if (dir < h->tamanho_atual && eh_mais_prioritario(h->vetor[dir], h->vetor[maior_prio])) {
        maior_prio = dir;
    }

    if (maior_prio != indice) {
        troca(&h->vetor[indice], &h->vetor[maior_prio]);
        desce_heap(h, maior_prio);
    }
}



HEAP* heap_criar(int capacidade) {
    HEAP* h = (HEAP*) malloc(sizeof(HEAP));
    if (h != NULL) {
        // Aloca o vetor linear com o tamanho definido pelo usuário
        h->vetor = (ELEMENTO_HEAP*) malloc(sizeof(ELEMENTO_HEAP) * capacidade);
        h->capacidade_max = capacidade;
        h->tamanho_atual = 0;
        h->contador_global = 0;
    }
    return h;
}

void heap_destruir(HEAP* h) {
    if (h != NULL) {
        free(h->vetor);
        free(h);
    }
}

bool heap_inserir(HEAP* h, Paciente paciente, int prioridade) {
    if (h == NULL || h->tamanho_atual >= h->capacidade_max) return false;
    
    // Cria o envelope
    ELEMENTO_HEAP novo_elemento;
    novo_elemento.dados_paciente = paciente; 
    novo_elemento.prioridade = prioridade;
    novo_elemento.ordem_chegada = h->contador_global++;

    // Insere no final do vetor linear
    h->vetor[h->tamanho_atual] = novo_elemento;
    
    // Ajusta a propriedade do heap (Sobe)
    sobe_heap(h, h->tamanho_atual);
    
    h->tamanho_atual++;
    return true;
}

Paciente heap_remover(HEAP* h) {
    if (h == NULL || h->tamanho_atual == 0) {
        // Retorna um paciente inválido/vazio se o heap estiver vazio
        Paciente vazio;
        vazio.id = -1; 
        return vazio;
    }

    // Extrai o paciente do envelope que está na raiz (índice 0)
    Paciente retorno = h->vetor[0].dados_paciente;

    // Move o último para o início
    h->vetor[0] = h->vetor[h->tamanho_atual - 1];
    h->tamanho_atual--;

    if (h->tamanho_atual > 0) {
        desce_heap(h, 0);
    }

    return retorno;
}

bool heap_cheia(HEAP* h) {
    return h->tamanho_atual == h->capacidade_max;
}

bool heap_vazia(HEAP* h) {
    return h->tamanho_atual == 0;
}

Paciente* buscar_paciente_no_heap(HEAP* h, int id) {
    if (h == NULL || h->tamanho_atual == 0) {
        return NULL;
    }

    // Percorre o vetor linearmente (O(N))
    for (int i = 0; i < h->tamanho_atual; i++) {
        if (h->vetor[i].dados_paciente.id == id) {
            // Retorna o ENDEREÇO do paciente que está dentro do vetor
            return &(h->vetor[i].dados_paciente); 
        }
    }

    // Se percorreu tudo e não achou
    return NULL;
}


void heap_listar_pacientes(HEAP* h) {

    if (h == NULL || h->tamanho_atual == 0) {
        printf("A fila de triagem (Heap) esta vazia.\n");
        return;
    }

    printf("\n--- PACIENTES NA FILA DE ESPERA (Visao do Sistema) ---\n");
    printf("Total na fila: %d\n", h->tamanho_atual);
    
    // Iteração linear sobre o vetor
    for (int i = 0; i < h->tamanho_atual; i++) {
        Paciente p = h->vetor[i].dados_paciente;
        int prioridade = h->vetor[i].prioridade;
        int chegada = h->vetor[i].ordem_chegada;


        printf("[%d] ID: %d | Nome: %-20s | Prio: %d | Chegada: %d\n", 
               i, p.id, p.nome, prioridade, chegada);
    }
    printf("------------------------------------------------------\n");
}