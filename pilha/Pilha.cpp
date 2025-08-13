#include <stdio.h>
#include "Pilha.hpp"
#include <iostream>

bool Cria_Pilha(Pilha *p, int tamanho) {
    p->topo = -1;
    p->capacidade = tamanho;
    p->dado = new int[tamanho];
}

void Empilha(Pilha *p, int Dado) {
    if(Pilha_cheia(p)){
        printf("Pilha cheia \n");
    }
    p->dado[p->topo]=Dado;
    p->topo++;
}

bool Desempilha(Pilha *p) {
    if(p->topo == -1){
        printf("Pilha vazia \n");
        return;
    }
    p->topo--;
    return p->dado;
}

int Tamanho_Pilha(Pilha *p){
    return p->topo + 1;
}

int Capacidade_pilha(Pilha *p){
    return p->capacidade - p->topo - 1;
}

bool Pilha_cheia(Pilha *p) {
    if (p->topo == p->capacidade - 1) {
        printf("Pilha cheia \n");
        return true;
    }
    return false;
}

bool Pilha_vazia(Pilha *p) {
    if (p->topo == -1) {
        printf("Pilha vazia /n");
        return true;
    }
    return false;
}

bool Deleta_Pilha(Pilha *p){
    for (int i=0; i< p->topo; i++){
        p->dado[i] = 0;
    }
    p->topo = -1;
    p->capacidade = 0;
}



int main() {


    return 0;
}
