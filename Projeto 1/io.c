#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "paciente.h" 
#include "pilha.h"
#include "lista.h"
#include "fila.h"


void salvar_sistema(LISTA* lista, FILA* fila) {
    // Abre o arquivo em modo "write binary" (escrita binária)
    FILE* arquivo = fopen(NOME_ARQUIVO_DADOS, "wb");
    if (arquivo == NULL) {
        printf("ERRO CRITICO: Nao foi possivel abrir o arquivo para salvar os dados.\n");
        return;
    }
    // 1. Salvar contadores gerais
    int total_pacientes_lista = lista->tamanho;
    int total_pacientes_fila = fila->tamanho_atual;
    fwrite(&total_pacientes_lista, sizeof(int), 1, arquivo);
    fwrite(&total_pacientes_fila, sizeof(int), 1, arquivo);
    fwrite(&(fila->tamanho_max), sizeof(int), 1, arquivo);

    // 2. Salvar dados de cada paciente da LISTA GERAL
    NOLISTA* no_paciente = lista->inicio;
    
    while (no_paciente != NULL) {
        fwrite(&(no_paciente->paciente.id), sizeof(int), 1, arquivo);
        fwrite(no_paciente->paciente.nome, sizeof(char), TAMANHO_NOME, arquivo);

        PILHA* historico = no_paciente->paciente.historico;
        int total_procedimentos = historico->tamanho_atual;
        fwrite(&total_procedimentos, sizeof(int), 1, arquivo);
        
        NOPILHA* no_procedimento = historico->topo;
        while (no_procedimento != NULL) {
            fwrite(no_procedimento->procedimento, sizeof(char), TAMANHO_PROCEDIMENTO, arquivo);
            no_procedimento = no_procedimento->proximo;
        }
        no_paciente = no_paciente->proximo;
    }

    // 3. Salvar a FILA DE ESPERA (apenas os IDs)
    NOFILA* no_fila = fila->inicio;
    while(no_fila != NULL){
        fwrite(&(no_fila->Paciente.id), sizeof(int), 1, arquivo);
        no_fila = no_fila->proximo;
    }

    fclose(arquivo);
    printf("Dados do sistema salvos com sucesso em '%s'.\n", NOME_ARQUIVO_DADOS);
}


// --- FUNÇÃO DE CARREGAR ---
void carregar_sistema(LISTA** p_lista, FILA** p_fila) {
    // Abre o arquivo em modo "read binary" (leitura binária)
    FILE* arquivo = fopen(NOME_ARQUIVO_DADOS, "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando um novo sistema...\n");
        *p_lista = cria_lista();
        *p_fila = criar_fila(5); 
        return;
    }

    // 1. Carregar contadores gerais
    int total_pacientes_lista, total_pacientes_fila, capacidade_fila;
    fread(&total_pacientes_lista, sizeof(int), 1, arquivo);
    fread(&total_pacientes_fila, sizeof(int), 1, arquivo);
    fread(&capacidade_fila, sizeof(int), 1, arquivo);

    *p_lista = cria_lista();
    *p_fila = criar_fila(capacidade_fila);

    // 2. Carregar dados de cada paciente para a LISTA GERAL
    for (int i = 0; i < total_pacientes_lista; i++) {
        Paciente p;
        p.historico = criar_pilha();

        fread(&(p.id), sizeof(int), 1, arquivo);
        fread(p.nome, sizeof(char), TAMANHO_NOME, arquivo);
        
        int total_procedimentos;
        fread(&total_procedimentos, sizeof(int), 1, arquivo);
        
        // Para manter a ordem LIFO, lemos os procedimentos e os inserimos em uma pilha temporária
        PILHA* temp_pilha = criar_pilha();
        char buffer_procedimento[TAMANHO_PROCEDIMENTO];
        for (int j = 0; j < total_procedimentos; j++) {
            fread(buffer_procedimento, sizeof(char), TAMANHO_PROCEDIMENTO, arquivo);
            pilha_push(temp_pilha, buffer_procedimento); 
        }

        while(!historico_vazio(temp_pilha)){
            pilha_pop(temp_pilha, buffer_procedimento);
            pilha_push(p.historico, buffer_procedimento);
        }
        destruir_pilha(temp_pilha);

        inserir_paciente(*p_lista, p);
    }

    // 3. Recriar a FILA DE ESPERA a partir dos IDs
    for(int i = 0; i < total_pacientes_fila; i++){
        int id_paciente_fila;
        fread(&id_paciente_fila, sizeof(int), 1, arquivo);
        Paciente* paciente_encontrado = buscar_paciente_por_id(*p_lista, id_paciente_fila);
        if(paciente_encontrado != NULL){
            inserir_paciente_fila(*p_fila, *paciente_encontrado);
        }
    }

    fclose(arquivo);
    printf("Dados do sistema carregados com sucesso de '%s'.\n", NOME_ARQUIVO_DADOS);
}
