#ifndef IO_H
#define IO_H

#include "lista.h"
#include "fila.h"

#define NOME_ARQUIVO_DADOS "hospital_data.bin"


void salvar_sistema(LISTA* lista, FILA* fila);
void carregar_sistema(LISTA** p_lista, FILA** p_fila);

#endif 