#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define K 1024

#define NUM_BITS_TAG_C01 14		
#define NUM_BITS_TAG_C02 14		
#define NUM_BITS_LINHA 11
#define NUM_BITS_BYTE 4

// ESTADOS
#define INVALIDO 0
#define VALIDO 1

// w = 4, s = 25, tag = 14, linha = 11, byte = 4;

typedef struct linha {
    char p1[NUM_BITS_BYTE + 1];
    char p2[NUM_BITS_BYTE + 1];
    char p3[NUM_BITS_BYTE + 1];
    char p4[NUM_BITS_BYTE + 1];
} Linha;

typedef struct cache01 {
    int estado[NUM_BITS_TAG_C01];
    char tag[NUM_BITS_TAG_C01];
    Linha linhacache[2*K];
} Cache01;

typedef struct cache02 {
    int estado[NUM_BITS_TAG_C02];
    char tag[NUM_BITS_TAG_C02];
    Linha linhacache[2*K];
} Cache02;

Cache01 CacheDados;
Cache02 CacheInstrucoes;

void InicializaCaches() {			// Função utilizada pelo main
	int i;
	
	for (i = 0; i<NUM_BITS_TAG_C01; i++) {
		CacheDados.estado[i] = INVALIDO;
	}
	
	for (i = 0; i<NUM_BITS_TAG_C02; i++) {
		CacheInstrucoes.estado[i] = INVALIDO;
	}
}

void readDataCache {		// Utiliza o CDB
	
}
