#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define K 1024

#define NUM_BITS_TAG 14				
#define NUM_BITS_LINHA 11
#define NUM_BITS_BYTE 4

// ESTADOS
#define INVALIDO 0
#define VALIDO 1

// w = 4, s = 25, tag = 14, linha = 11, byte = 4;

typedef struct linha {
    unsigned int p1;
    unsigned int p2;
    unsigned int p3;
    unsigned int p4;
} Linha;

typedef struct cache {
    int estado[2*K];
    int tag[2*K];
    Linha linhacache[2*K];
} Cache;

Cache CacheDados;
Cache CacheInstrucoes;

void InicializaCaches() {			// Função utilizada pelo main
	int i;
	
	for (i = 0; i<NUM_BITS_TAG; i++) {
		CacheDados.estado[i] = INVALIDO;
		CacheInstrucoes.estado[i] = INVALIDO;
	}
}

void readDataCache(unsigned int address) {		// Utiliza o CDB
	int line, tag, byte;
	int buffer;					// Simboliza um buffer genérico
	
	line = (address << NUM_BITS_TAG) >> (32 - NUM_BITS_LINHA);
	
	if (CacheDados.estado[line] == VALIDO) {
		tag = address >> (32 - NUM_BITS_TAG);
		
		if (CacheDados.tag[line] == tag) {
			byte = (address << (32 - NUM_BITS_BYTE)) >> (32 - NUM_BITS_BYTE);
			
			switch (byte) {
				case 0:
					InsereFilaCDB(&FilaCDB, CacheDados.Linha[line].p1);
					break;
				case 1:
					InsereFilaCDB(&FilaCDB, CacheDados.Linha[line].p2);
					break;
				case 2:
					InsereFilaCDB(&FilaCDB, CacheDados.Linha[line].p3);
					break;
				case 3:
					InsereFilaCDB(&FilaCDB, CacheDados.Linha[line].p4);
					break;
			}
		}
		else {
			buffer = address;
			CMB.address = (buffer >> NUM_BITS_BYTE) << NUM_BITS_BYTE;
			CMB.controle = OCUPADO;
			
			readRAM();
			writeDataCache_ViaCMB();
			
			buffer = CMB.dados;
			InsereFilaCDB(&FilaCDB, buffer);
			//INCREMENTA CICLOS GASTOS
		}
	}
	else {
		buffer = address;
		CMB.address = (buffer >> NUM_BITS_BYTE) << NUM_BITS_BYTE;
		CMB.controle = OCUPADO;
		
		readRAM();
		writeDataCache_ViaCMB();
		
		buffer = CMB.dados;
		InsereFilaCDB(&FilaCDB, buffer);
		//INCREMENTA CICLOS GASTOS
	}
}

void writeDataCache_ViaCMB() {
	
}
