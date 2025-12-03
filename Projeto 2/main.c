#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "paciente.h"
#include "fila.h"
#include "lista.h"
#include "io.h"

void mostrar_menu();
void registrar_paciente_interface(LISTA* lista, FILA* fila);



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