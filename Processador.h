#include <stdio.h>
#include <MemoriaCache.h>
#include <MemoriaRAM.h>
#include <ModeloListaEstagiosProcessador.h>

#define NUM_ESTACOES 30
	#define NUM_EST_ARIT 20
	#define NUM_EST_LS 5
	#define NUM_EST_MULDIV 5
#define NUM_REGS 32

typedef struct estacao_reserva {
	unsigned int Busy;
	unsigned int Op;
	unsigned int Vj;
	unsigned int Vk;
	unsigned int Qj;
	unsigned int Qk;
	unsigned int A;
} EstacaoReserva;

typedef int Status;
typedef int Registrador;


ListaEstagio FilaDeBusca;

FilaInstrucoes FilaDeDecod;

EstacaoReserva RS[NUM_ESTACOES];
Registrador Regs[NUM_REGS];
Status RegisterStats[NUM_REGS];		//Qi de um registrador X


int Processa(char *MCacheInst, char *MCacheDados, char *MRAM) {
	
	void BuscaInstruc(char *MCacheInst, char *MCacheDados, char *MRAM);
	void DecodificaInstruc();
	void ExecutaInstruc();
	void CompletaInstruc();
	
	
	IniciaLista(&FilaDeBusca);
	IniciaFilaDecod(&FilaDeDecod);
	
	BuscaInstruc(MCache, MRAM);
	while (FilaDeBusca->prox != NULL) {
		CompletaInstruc();
		ExecutaInstruc();
		DecodificaInstruc();
		BuscaInstruc(MCache, MRAM);
	}
	
	
	
	
	void BuscaInstruc(char *MCacheInst, char *MCacheDados, char *MRAM) {
		
		char *instruc;
		unsigned int instrucao;
		int i;
		
		for (i = 1; i <= CAPACIDADE_DE_BUSCA; i++) {
			instruc = CapturaDadoNaCache(MCacheInst);
			if (instruc == NULL) {         //Se deu miss na cache
				instruc = readRAM(MRAM, PC_Counter, 4);
			}
			
			instrucao = atoi(instruc);  //Usar atoi?..
			InsereListaFim(FilaDeBusca, instrucao, (-1));
			
			PC_Counter = PC_Counter + 4;
		}
	}
	
	void DecodificaInstruc() {
		
		node *Instruc = FilaDeDecod->prox;
		nodeDecod = InfoInstruc = NULL;
		
		int i;
		int numCiclos, OpCode, OperandoA, OperandoB;
		
		for (i = 1; i<=FilaDeDecod->TamLista; i++) {
			if (Instruc->ciclosrestantes > 0) {
				(Instruc->ciclosrestantes)--;
			}
			else {
				
			}
			
			Instruc = Instruc->prox;
		}
		
		while (FilaDeDecod->TamLista != CAPACIDADE_DE_DECODIFICACAO) {
			Instruc = RemoveLista(FilaDeBusca, 1);
			
			//DECODIFICA INSTRUCAO - TEM QUE SABER CICLOS DE CADA TIPO DE INSTRUC e ONDE 
			//ESTAO os bits do op-code e operandos em cada operacao
			
			InsereFilaDecod(FilaDeDecod, OpCode, OperandoA, OperandoB, Destino, numCiclos, numCiclos);
		}
	}
}

