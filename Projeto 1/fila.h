#include <stdbool.h>

#ifndef FILA_H
	#define FILA_H
	#include "paciente.h"


	typedef struct fila_ FILA;

	typedef struct no_f NOFILA;

	struct no_f{
		Paciente Paciente;
		NOFILA *proximo;
	};

	struct fila_{
		NOFILA *inicio;
		NOFILA *fim;
		int tamanho_atual;
		int tamanho_max;
	};
	
	FILA *criar_fila();
	bool inserir_paciente_fila(FILA *fila, Paciente paciente);
	Paciente remover_paciente_fila(FILA* fila);
	bool fila_vazia(FILA *fila);
	bool fila_cheia(FILA *fila);
	void mostrar_fila_espera(FILA* fila);
	void destruir_fila(FILA* fila);
	bool buscar_paciente_na_fila(FILA* fila, int id);
	  
#endif
