#ifndef IO_H
#define IO_H

#include "heap.h"
#include "lista.h"

#define NOME_ARQUIVO_DADOS "hospital_data.bin"


void salvar_sistema(HEAP* h, LISTA* l);
void carregar_sistema(HEAP** h,LISTA *l);

#endif 