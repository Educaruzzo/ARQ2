
#include <stdio.h>
#include <stdlib.h>

#define LIVRE 0
#define OCUPADO 1

typedef struct barramento {
	unsigned int controle;		// Ocupado ou livre
	unsigned int dados;		// Dados passando no barramento
	unsigned int address;		// Endereco destino do dado
} Barramento;

Barramento CDB = {0, 0, 0};		// Common Data Bus
Barramento CMB = {0, 0, 0};		// Cache-Memory Bus
Barramento CFB = {0, 0, 0};		// Cache-Fetch (Stage) Bus


int InsereDadosBarramento (Barramento *B, int Dados, int Endereco) {
	if ((*B) == LIVRE) {
		(*B).dados = Dados;
		(*B).address = Endereco;
		(*B).controle = OCUPADO;
		return 1;
	}
	else {
		return 0;		// Barramento Ocupado
	}
}

void LiberaBarramento (Barramento *B) {
	(*B).controle = LIVRE;
}
