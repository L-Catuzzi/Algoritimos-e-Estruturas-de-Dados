#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include "paciente.h" 


typedef struct heap_ HEAP;

typedef struct {
    Paciente dados_paciente; 
    int prioridade;          // 1 a 5
    int ordem_chegada;       // Para desempate (FIFO)
} ELEMENTO_HEAP;

struct heap_ {
    ELEMENTO_HEAP* vetor;    // Vetor linear de envelopes
    int tamanho_atual;
    int capacidade_max;
    int contador_global;     // Relógio lógico para ordem de chegada
};

// --- Funções de Gerenciamento ---

/**
 * @brief Cria um heap com capacidade definida pelo usuário.
 * @param capacidade Tamanho máximo do vetor interno.
 */
HEAP* heap_criar(int capacidade);

void heap_destruir(HEAP* h);

/**
 * @brief Insere um paciente na fila de prioridade.
 * @param h O Heap.
 * @param paciente A struct Paciente completa (vinda do paciente.h).
 * @param prioridade O nível de urgência (1=Emergência ... 5=Não Urgente).
 * @return true se sucesso, false se o heap estiver cheio.
 */
bool heap_inserir(HEAP* h, Paciente paciente, int prioridade);

/**
 * @brief Remove e retorna o paciente mais prioritário.
 * @return A struct Paciente original. (Se vazio, retorna paciente com ID -1).
 */
Paciente heap_remover(HEAP* h);
bool heap_cheia(HEAP* h);
bool heap_vazia(HEAP* h);
Paciente* buscar_paciente_no_heap(HEAP* h, int id);

void heap_listar_pacientes(HEAP* h);

#endif 