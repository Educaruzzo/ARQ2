#include <stdio.h>
#include <stdlib.h>

int pulsoClock;		// processador tem uma intrução que seta isso em 0

void AcionarClock () {
	pulsoClock = 1;
	while (pulsoClock) {
		
		Processa();
		
	}
}
