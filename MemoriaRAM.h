#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 1048576

#define TAM_MEM_TEXT 8388607
#define INI_MEM_DATE 8388608
#define MAX_ADRESS (512*M)


char memoriaRAM[512*M + 1];


/*char *readRAM(char *memoriaRAM, unsigned int adress, int numposicoes) {

    int i, adressCopy;
    char *palavra = (char*) malloc(numposicoes+1);

    adressCopy = adress;
    for(i = 0; i <= (numposicoes - 1); i++) {
        palavra[i] = memoriaRAM[adressCopy];
        adressCopy++;
    }

    i++;
    palavra[i] = '\0';

    return palavra;
} */

void readRAM() {
	
	unsigned int i, addressCopy;
	unsigned int dadoRetorno = 0;

    	for(i = 0; i <= (CMB.dados - 1); i++) {
        	dadoRetorno = dadoRetorno | memoriaRAM[CMB.address + i];
        	dadoRetorno = dadoRetono << 8;
    	}
    	
	CMB.dados = dadoRetorno;
	// CMB.address = MontaEnderecoCache();
	CMB.controle = OCUPADO;
}

/*bool writeRAM(char *memoriaRAM, unsigned int adress, char *dado) {

    int i, adressCopy;

    if (adress >= INI_MEM_DATE) {
        adressCopy = adress;
        for(i = 0; i <= 3; i++) {
            memoriaRAM[adressCopy] = dado[i];
            adressCopy++;
        }
    }
    else {
        return false;
    }

    return true;
}*/

void writeRAM() {

    unsigned int MASK = 255;  // Ultimos 8 bits são 1's

    for(i = 3; i >= 0; i--) {
    	memoriaRAM[CMB.address + i] = (CMB.dados & MASK);
        MASK = MASK << 8;
    }
}
