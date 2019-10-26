#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main(int argc, char const *argv[]) {
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
			case 'q':
				destroiLista(processos);
				continua = 0;
			break;
		}
	}

	return 0;
}