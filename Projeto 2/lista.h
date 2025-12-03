#ifndef LISTA_H
    #define LISTA_H
    #include "paciente.h"

    typedef struct no_l NOLISTA;
    typedef struct lista_ LISTA;
    
    struct lista_ {
        NOLISTA* inicio;  
        NOLISTA* fim;     
        int tamanho;      
    };

    struct no_l {
        Paciente paciente;               
        NOLISTA* proximo;  
        NOLISTA* anterior; 
    };
    LISTA* cria_lista();
    void inserir_paciente(LISTA *lista, Paciente paciente);
    void apagar_paciente(LISTA *lista, int id);
    Paciente buscar_paciente(LISTA *lista, char nome[]);
    Paciente* buscar_paciente_por_id(LISTA* lista, int id);
    void listar_pacientes(LISTA *lista);
    void destruir_lista(LISTA* lista);




#endif