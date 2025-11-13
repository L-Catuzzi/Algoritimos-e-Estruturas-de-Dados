#include "paciente.h"
#include "pilha.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

PILHA* criar_pilha() {
    PILHA* nova_pilha = (PILHA*) malloc(sizeof(PILHA));
    if (nova_pilha != NULL) {
        nova_pilha->topo = NULL;
        nova_pilha->tamanho_atual = 0;
        nova_pilha->tamanho_maximo = MAX_PROCEDIMENTOS;
    }
    return nova_pilha;
}

int pilha_push(PILHA* pilha, const char* procedimento) {
    if (historico_cheio(pilha)) {
        printf("Erro: Historico de procedimentos cheio!\n");
        return 0;
    }
    NOPILHA* novo_no = (NOPILHA*) malloc(sizeof(NOPILHA));
    if (!novo_no) return 0;
    
    strcpy(novo_no->procedimento, procedimento);
    novo_no->proximo = pilha->topo;
    pilha->topo = novo_no;
    pilha->tamanho_atual++;
    return 1;
}

char* pilha_pop(PILHA* pilha, char* buffer_saida) {
    if (historico_vazio(pilha)) {
        printf("Historico de procedimentos vazio!\n");
        return NULL;
    }
    NOPILHA* no_removido = pilha->topo;
    strcpy(buffer_saida, no_removido->procedimento);
    pilha->topo = pilha->topo->proximo;
    free(no_removido);
    pilha->tamanho_atual--;
    return buffer_saida;
}

bool historico_vazio(PILHA* pilha) { return (pilha->tamanho_atual == 0); }
bool historico_cheio(PILHA* pilha) { return (pilha->tamanho_atual == pilha->tamanho_maximo); }

const char* consultar_procedimento(PILHA* pilha) {
    if (historico_vazio(pilha)){
        return "Historico vazio.";
    }
    return pilha->topo->procedimento;
}

void mostrar_historico(PILHA* pilha) {
    if (historico_vazio(pilha)) {
        printf("\n>>> Historico do paciente esta vazio. <<<\n");
        return;
    }
    NOPILHA* aux = pilha->topo;
    printf("\n--- HISTORICO DO PACIENTE (%d/%d) ---\n(Mais recente -> Mais antigo)\n", pilha->tamanho_atual, pilha->tamanho_maximo);
    while (aux != NULL) {
        printf("-> %s\n", aux->procedimento);
        aux = aux->proximo;
    }
    printf("--- FIM DO HISTORICO ---\n");
}

void destruir_pilha(PILHA* pilha) {
    char buffer[TAMANHO_PROCEDIMENTO];
    while (!historico_vazio(pilha)) {
        pilha_pop(pilha, buffer);
    }
    free(pilha);
}


void adicionar_procedimento(LISTA* lista_pacientes, int id_paciente, const char* procedimento) {
    Paciente* paciente_alvo = buscar_paciente_por_id(lista_pacientes, id_paciente);

    // 2. Tratar caso de paciente não encontrado
    if (paciente_alvo == NULL) {
        printf("\nERRO: Paciente com ID %d nao foi encontrado.\n", id_paciente);
        return;
    }

    printf("\nAdicionando procedimento para o paciente '%s'...\n", paciente_alvo->nome);
    if (pilha_push(paciente_alvo->historico, procedimento)) {
        printf("Procedimento adicionado com sucesso: \"%s\"\n", procedimento);
    }
}

void desfazer_procedimento(LISTA* lista_pacientes, int id_paciente) {
    // 1. Localizar o paciente
    Paciente* paciente_alvo = buscar_paciente_por_id(lista_pacientes, id_paciente);

    if (paciente_alvo == NULL) {
        printf("\nERRO: Paciente com ID %d nao foi encontrado.\n", id_paciente);
        return;
    }

    printf("\nDesfazendo procedimento para o paciente '%s'\n", paciente_alvo->nome);
    char procedimento_desfeito[TAMANHO_PROCEDIMENTO];

    if (pilha_pop(paciente_alvo->historico, procedimento_desfeito) != NULL) {
        printf("Procedimento desfeito: \"%s\"\n", procedimento_desfeito);
    } else {
        printf("Nao ha procedimentos a desfazer para este paciente.\n");
    }
}