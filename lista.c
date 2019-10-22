#include "lista.h"
#include <stdlib.h>
#include <string.h>

#define MAX_DESCR 51

typedef struct Horario {
	int hh;
	int mm;
	int ss;
} horario;

typedef struct Celula {
	int prior; //valor indicando prioridade que está entre 1 e 99
	horario chegada;
	char descricao[MAX_DESCR];

	struct Celula* prox;
} celula;

typedef struct Lista {
	celula* primeiro;
	celula* ultimo;

	int tam;
	celula* maiorP;
	celula* menorT;
} lista;

lista* criaLista() {
	lista* nova = (lista* ) malloc(sizeof(lista));

	if (nova) {
		nova->primeiro = NULL;
		nova->ultimo = NULL;

		nova->tam = 0;
		nova->maiorP = NULL;
		nova->menorT = NULL;
	}
	return nova;
}

celula* criaCelula(int prior, horario chegada, char descricao[]) {
	celula* nova = (celula*) malloc(sizeof(celula));

	if (nova) {
		nova->prior = prior;
		nova->chegada = chegada;
		strcpy(nova->descricao, descricao);
	}
	return nova;
}

void insereAux(lista* l, celula* c) {
	c->prox = l->primeiro;
	l->primeiro = c;

	(l->tam)++;
	if (l->tam == 1) {
		l->maiorP = c;
		l->menorT = c;
	}
	else {
		if (c->prior > l->maiorP->prior)  l->maiorP = c;
		//falta implementar comparação de horarios!!!!
	}

}

void insereNaLista(lista* l, int prior,  horario chegada, char descricao[]) {
	celula* nova = criaCelula(prior, chegada, descricao);
	insereAux(l, nova);
}