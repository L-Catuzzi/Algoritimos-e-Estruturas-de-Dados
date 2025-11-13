#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "paciente.h"
#include "pilha.h"
#include "fila.h"
#include "lista.h"
#include "io.h"

void mostrar_menu();
void registrar_paciente_interface(LISTA* lista, FILA* fila);
void registrar_obito_interface(LISTA* lista, FILA* fila);
void chamar_paciente_interface(FILA* fila);
void mostrar_historico_interface(LISTA* lista);


int main() {
    LISTA* lista_geral = NULL;
    FILA* fila_de_espera = NULL;
    int opcao = 0;

   
    carregar_sistema(&lista_geral, &fila_de_espera);

    printf("Bem-vindo ao Sistema de Simulacao de Pronto Socorro!\n");

    do {
        mostrar_menu();
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                registrar_paciente_interface(lista_geral, fila_de_espera);
                break;
            case 2:
                registrar_obito_interface(lista_geral, fila_de_espera);
                break;
            case 3:
                {
                    int id_paciente;
                    char procedimento[TAMANHO_PROCEDIMENTO];
                    printf("Digite o ID do paciente: ");
                    scanf("%d", &id_paciente);
                    getchar();
                    printf("Digite o procedimento a ser adicionado: ");
                    fgets(procedimento, TAMANHO_PROCEDIMENTO, stdin);
                    procedimento[strcspn(procedimento, "\n")] = 0;
                    adicionar_procedimento(lista_geral, id_paciente, procedimento);
                }
                break;
            case 4:
                {
                    int id_paciente;
                    printf("Digite o ID do paciente para desfazer o procedimento: ");
                    scanf("%d", &id_paciente);
                    getchar();
                    desfazer_procedimento(lista_geral, id_paciente);
                }
                break;
            case 5:
                chamar_paciente_interface(fila_de_espera);
                break;
            case 6:
                mostrar_fila_espera(fila_de_espera);
                break;
            case 7:
                mostrar_historico_interface(lista_geral);
                break;
            case 8:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 8);

    // REQUISITO 6: Ao sair do sistema, armazenar todas as informações.
    salvar_sistema(lista_geral, fila_de_espera);

    // Limpeza final de toda a memória alocada
    destruir_lista(lista_geral);
    destruir_fila(fila_de_espera);

    printf("Sistema encerrado. Memoria liberada.\n");
    return 0;
}

// --- Implementação das Funções da Interface ---

void mostrar_menu() {
    printf("\n============== MENU PRINCIPAL ==============\n");
    printf("1. Registrar paciente\n");
    printf("2. Registrar obito de paciente (por ID)\n");
    printf("3. Adicionar procedimento ao historico\n");
    printf("4. Desfazer ultimo procedimento\n");
    printf("5. Chamar paciente para atendimento\n");
    printf("6. Mostrar fila de espera\n");
    printf("7. Mostrar historico de um paciente\n");
    printf("8. Sair\n");
    printf("==========================================\n");
    printf("Escolha uma opcao: ");
}

void registrar_paciente_interface(LISTA* lista, FILA* fila) {
    Paciente novo_paciente;
    printf("--- Registrar Novo Paciente ---\n");
    printf("Digite o ID do novo paciente: ");
    scanf("%d", &novo_paciente.id);
    getchar();

    // REQUISITO 5.1: Não aceitar IDs repetidos
    if (buscar_paciente_por_id(lista, novo_paciente.id) != NULL) {
        printf("ERRO: ID %d ja existe no sistema. Cadastro cancelado.\n", novo_paciente.id);
        return;
    }

    printf("Digite o nome do novo paciente: ");
    fgets(novo_paciente.nome, TAMANHO_NOME, stdin);
    novo_paciente.nome[strcspn(novo_paciente.nome, "\n")] = 0;
    
    novo_paciente.historico = criar_pilha();
    if (novo_paciente.historico == NULL) return;

    // REQUISITO 5.1: Inserir na lista E na fila
    inserir_paciente(lista, novo_paciente);
    if (inserir_paciente_fila(fila, novo_paciente)) {
        printf("Paciente '%s' registrado no sistema e adicionado a fila de espera.\n", novo_paciente.nome);
    } else {
        printf("Paciente '%s' registrado no sistema, mas a fila de espera esta cheia!\n", novo_paciente.nome);
    }
}

void registrar_obito_interface(LISTA* lista, FILA* fila) {
    int id_busca;
    printf("--- Registrar Obito de Paciente ---\n");
    printf("Digite o ID do paciente: ");
    scanf("%d", &id_busca);
    getchar();

    if (buscar_paciente_por_id(lista, id_busca) == NULL) {
        printf("ERRO: Paciente com ID %d nao existe no sistema.\n", id_busca);
        return;
    }

    // REQUISITO 5.2: "Caso ainda esteja na fila de espera, é proibido morrer!"
    if (buscar_paciente_na_fila(fila, id_busca)) {
        printf("ERRO: O paciente com ID %d ainda esta na fila de espera e nao pode ter o obito registrado.\n", id_busca);
        printf("Chame o paciente para atendimento primeiro.\n");
        return;
    }

    
    apagar_paciente(lista, id_busca);
}

void chamar_paciente_interface(FILA* fila) {
    printf("--- Chamar Paciente para Atendimento ---\n");
    // REQUISITO 5.4: Tirar o paciente da fila!
    Paciente paciente_chamado = remover_paciente_fila(fila);

    if (paciente_chamado.id != -1) {
        printf("PROXIMO PACIENTE: '%s' (ID: %d), por favor, dirija-se ao consultorio.\n",
               paciente_chamado.nome, paciente_chamado.id);
    }
    
}

void mostrar_historico_interface(LISTA* lista) {
    int id_busca;
    printf("--- Consultar Historico Medico ---\n");
    printf("Digite o ID do paciente: ");
    scanf("%d", &id_busca);
    getchar();
    Paciente* paciente = buscar_paciente_por_id(lista, id_busca);
    if (paciente != NULL) {
        mostrar_historico(paciente->historico);
    }
    else{
        printf("Paciente com id %d nao encontrado\n", paciente->id);
    }
}