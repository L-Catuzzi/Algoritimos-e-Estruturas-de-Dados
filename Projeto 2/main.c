#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "lista.h"
#include "io.h"
#include "heap.h"

void mostrar_menu();
void registrar_paciente_interface(HEAP* h, LISTA* l); 
void remover_paciente_interface(HEAP* h, LISTA *l);
void listar_pacientes_interface(LISTA* l);
void mostrar_fila_espera(HEAP* h);
void dar_alta_paciente(HEAP* h);
void buscar_paciente_interface(LISTA* l);

int main() {
    HEAP* fila_espera = NULL;
    LISTA *lista_geral = cria_lista();
    int opcao = 0;
    
    carregar_sistema(&fila_espera, lista_geral);
   

    printf("Bem-vindo ao Sistema de Simulacao de Pronto Socorro!\n");

    do {
        mostrar_menu();
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                registrar_paciente_interface(fila_espera, lista_geral);
                break;
            case 2: // Vamos alterar para remover 
                remover_paciente_interface(fila_espera,lista_geral);
                break;
            case 3: // Listar pacientes
                listar_pacientes_interface(lista_geral);
                break;
            case 4:// buscar por id
                buscar_paciente_interface(lista_geral);
                break;
            case 5: // Maior para menor prioridade
                mostrar_fila_espera(fila_espera);
                break;
            case 6:// Dar alta ao paciente
                dar_alta_paciente(fila_espera);
                break;
            case 7:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 7);
    salvar_sistema(fila_espera, lista_geral);

    destruir_lista(lista_geral);
    heap_destruir(fila_espera);
    printf("Sistema encerrado. Memoria liberada.\n");
    return 0;
}

// --- Implementação das Funções da Interface ---

void mostrar_menu() {
    printf("\n============== MENU PRINCIPAL ==============\n");
    printf("1. Registrar paciente\n");
    printf("2. Remover paciente\n");
    printf("3. Listar pacientes\n");
    printf("4. Buscar paciente por ID\n");
    printf("5. Mostrar fila de espera\n");
    printf("6. Dar alta ao paciente\n");
    printf("7. Sair\n");
    printf("==========================================\n");
    printf("Escolha uma opcao: ");
}


// 1
void registrar_paciente_interface(HEAP *h, LISTA* l){
    if (l == NULL || h == NULL) {
        printf("ERRO CRITICO: Lista ou Heap nao inicializados.\n");
        return;
    }

    Paciente novo_paciente;
    
    printf("\n --------- Registrar Novo Paciente ----------\n");
    printf("Digite o id do paciente: ");
    scanf("%d", &novo_paciente.id);
    getchar(); 

    // 1. REGRA DE NEGÓCIO: ID Único
    // Verificamos na LISTA, pois ela contém TODO o histórico do hospital.
    if (buscar_paciente_por_id(l, novo_paciente.id) != NULL) {
        printf("ERRO: ID %d ja existe no cadastro do hospital!\n", novo_paciente.id);
        return;
    }

    // Segurança extra (checar se o id aparece na fila de espera)
    if (buscar_paciente_no_heap(h, novo_paciente.id) != NULL) {
        printf("ERRO: ID %d ja esta na fila de espera!\n", novo_paciente.id);
        return;
    }

    printf("Digite o nome do paciente: ");
    fgets(novo_paciente.nome, TAMANHO_NOME, stdin);
    novo_paciente.nome[strcspn(novo_paciente.nome, "\n")] = 0;

    printf("Digite a prioridade de atendimento (1=Emergencia ... 5=Nao Urgente): ");
    scanf("%d", &novo_paciente.prioridade);
    getchar();

    // O campo ordem_chegada será preenchido automaticamente pelo heap_inserir.

    
    // Primeiro: Registra no histórico permanente (LISTA)
    inserir_paciente(l, novo_paciente);
    
    // Segundo: Coloca na fila de espera (HEAP)
    bool inseriu_heap = heap_inserir(h, novo_paciente, novo_paciente.prioridade);

    if (inseriu_heap) {
        printf("SUCESSO: Paciente '%s' cadastrado e adicionado a fila de espera.\n", novo_paciente.nome);
    } else {
        printf("AVISO: Paciente cadastrado na lista, mas a FILA DE ESPERA (Heap) esta cheia!\n");
    }
}

//2
void remover_paciente_interface(HEAP* h, LISTA* l) {
    int id_remover;

    printf("\n--------- Remover Paciente do Sistema ---------\n");
    printf("Digite o ID do paciente a ser removido: ");
    scanf("%d", &id_remover);
    getchar(); 

    // 1. VERIFICAÇÃO CRÍTICA: O paciente está na fila de espera?
    if (buscar_paciente_no_heap(h, id_remover) != NULL) {
        printf("\n[ERRO]: O paciente (ID %d) ainda esta na fila de espera!\n", id_remover);
        printf("Voce nao pode apagar o registro enquanto ele aguarda atendimento.\n");
        printf("Dica: Use a opcao 'Dar Alta/Chamar' primeiro.\n");
        return;
    }

    // 2. Verifica se o paciente existe na Lista Geral
    Paciente* p = buscar_paciente_por_id(l, id_remover);
    if (p == NULL) {
        printf("\n[ERRO]: Paciente com ID %d nao encontrado no cadastro geral.\n", id_remover);
        return;
    }


    apagar_paciente_por_id(l, id_remover);
    printf("Operacao de remocao concluida.\n");
}

// 3
void listar_pacientes_interface(LISTA* l){
    listar_pacientes(l);
}

//4
void buscar_paciente_interface(LISTA* l){
    int id;
    printf("Insira o id do paciente que deseja buscar: ");
    scanf("%d", &id);
    buscar_paciente_por_id(l, id);
}


// 5
void mostrar_fila_espera(HEAP* h){
    heap_listar_pacientes(h);
}

// 6
void dar_alta_paciente(HEAP* h) {
    if (heap_vazia(h)) {
        printf("\n[AVISO] A fila de espera esta vazia. Ninguem para atender.\n");
        return;
    }

    // O heap_remover já traz o paciente de maior prioridade (e desempata por chegada)
    Paciente p = heap_remover(h);

    if (p.id != -1) {
        printf("\n=== CHAMANDO PACIENTE ===\n");
        printf("Nome: %s\n", p.nome);
        printf("ID: %d\n", p.id);
        
        // Exibe a prioridade para confirmar a lógica
        char* desc_prioridade = "";
        switch(p.prioridade) {
            case 1: desc_prioridade = "EMERGENCIA"; break;
            case 2: desc_prioridade = "MUITO URGENTE"; break;
            case 3: desc_prioridade = "URGENTE"; break;
            case 4: desc_prioridade = "POUCO URGENTE"; break;
            case 5: desc_prioridade = "NAO URGENTE"; break;
        }
        printf("Classificacao: %d - %s\n", p.prioridade, desc_prioridade);
        printf("=========================\n");
    }
}