#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main() {
	char cmd[8];
	horario horarioAux;
	int prior;
	char descricao[MAX_DESCR];
	char op;

	lista* processos;
	processos = criaLista();


	int continua = 1;
	while (continua) {
		scanf("%s", cmd);
		switch (cmd[0]) {
			case 'a':
				scanf("%d%d:%d:%d%s", &prior, &horarioAux.hh, &horarioAux.mm, &horarioAux.ss, descricao);
				insereNaLista(processos, prior, horarioAux, descricao);
			break;
			case 'p':
				scanf(" -%c", &op);
				if (op == 'p') printLista(processos, P);
				else if (op == 't') printLista(processos, T);
				else if (op == 'n') printLista(processos, N);
			break;
			case 'n':
				scanf(" -%c", &op);
				if (op == 'p') printNext(processos, P);
				else if (op == 't') printNext(processos, T);
			break;
			case 'e':
				scanf(" -%c", &op);
				if (op == 'p') rmCelula(processos, P);
				else if (op == 't') rmCelula(processos, T);
			break;
			case 'c':
				scanf(" -%c", &op);
				if (op == 'p') {
					int pAnterior;
					int pNovo;
					scanf(" %d|%d", &pAnterior, &pNovo);
					changePrior(processos, pAnterior, pNovo);
				}
				else if (op == 't') {
					horario hAnterior;
					horario hNovo;
					scanf(" %d:%d:%d|%d:%d:%d", &hAnterior.hh, &hAnterior.mm, &hAnterior.ss, &hNovo.hh, &hNovo.mm, &hNovo.ss);
					changeHorario(processos, hAnterior, hNovo);
				}
			break;
			case 'q':
				destroiLista(processos);
				continua = 0;
			break;
		}
	}

	return 0;
}