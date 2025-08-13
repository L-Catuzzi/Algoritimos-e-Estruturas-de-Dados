#include <iostream>
#include "char.hpp"

Char Cria_char(char nome[],int forca, int inteligencia, int agilidade, char classe[]) {
    Char *c = new Char;
    strcpy(c->nome, nome);
    c->forca = forca;
    c->inteligencia = inteligencia;
    c->agilidade = agilidade;
    strcpy(c->classe, classe);
    return *c;
}


void Deleta_char(Char *c) {
    delete c;
}
