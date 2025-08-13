typedef struct Pilha {
    int topo;
    int capacidade;
    int *dado;
} Pilha;

bool Cria_Pilha(Pilha *p, int tamanho); /*Função para criar pilha, retorna 1 se q criação for bem sucedida*/

void Empilha(Pilha *p, int Dado);/* Função para adicionar um dado à pilha*/

bool Desempilha(Pilha *p);/* Função para remover um dado da pilha*/

int Tamanho_Pilha(Pilha *p);/* Função para retornar o tamanho da pilha*/

int Capacidade_Pilha(Pilha *p);/* Função para retornar a capacidade da pilha*/

bool Pilha_Cheia(Pilha *p);/* Função para verificar se a pilha está cheia*/

bool Pilha_vazia(Pilha *p);/* Função para verificar se a pilha está vazia*/

bool Deleta_Pilha(Pilha *p);/* Função para deletar a pilha*/


