#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




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
} lista;

lista* criaLista() {
	lista* nova = (lista* ) malloc(sizeof(lista));

	if (nova) {
		nova->primeiro = NULL;
		nova->ultimo = NULL;

		nova->tam = 0;
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
	
	c->prox = NULL;
	if (l->tam == 0) {
		l->primeiro = c;
		l->ultimo = c;

	}
	else {
		l->ultimo->prox = c;
		l->ultimo = c;
	}
	(l->tam)++;
}

void insereNaLista(lista* l, int prior,  horario chegada, char descricao[]) {
	celula* nova = criaCelula(prior, chegada, descricao);
	insereAux(l, nova);
}

void destroiAux(celula* c) {
	if (c != NULL) {
		destroiAux(c->prox);
		free(c);
	}
}

/*void destroiIntervalo(celula* inicio, celula* fim) {
	celula* aux = inicio->prox;
	free(inicio);
	if (inicio != fim) destroiIntervalo(aux, fim);
}*/

void destroiLista(lista* l) {
	destroiAux(l->primeiro);
	free(l);
}

/*celula* encontraMeio(celula* inicio, celula* fim, int n) {
	int m = (n - 1)/2;
	for (int i = 0; i < m; i++) inicio = inicio->prox;
	return inicio;
}

void merge(celula** inicio, celula** meio, celula** fim, int tipoOrdena) {
	celula* inicio1 = *inicio;
	celula* inicio2 = (*meio)->prox;

	lista* lAux = criaLista();

	while (inicio1 != (*meio)->prox && inicio2 != (*fim)->prox) {
		switch (tipoOrdena) {
			case T:
				if ( menorQueHorario(inicio1->chegada, inicio2->chegada) ) {
					insereNaLista(lAux, inicio1->prior, inicio1->chegada, inicio1->descricao);
					inicio1 = inicio1->prox;
				}
				else {
					insereNaLista(lAux, inicio2->prior, inicio2->chegada, inicio2->descricao);
					inicio2 = inicio2->prox;
				}
			break;
			case P:
				if (inicio1->prior > inicio2->prior) {
					insereNaLista(lAux, inicio1->prior, inicio1->chegada, inicio1->descricao);
					inicio1 = inicio1->prox;
				}
				else {
					insereNaLista(lAux, inicio2->prior, inicio2->chegada, inicio2->descricao);
					inicio2 = inicio2->prox;
				}
			break;
		}
	}

	while (inicio1 != (*meio)->prox) {
		switch (tipoOrdena) {
			case T:
				insereNaLista(lAux, inicio1->prior, inicio1->chegada, inicio1->descricao);
				inicio1 = inicio1->prox;
			break;
			case P:
				insereNaLista(lAux, inicio1->prior, inicio1->chegada, inicio1->descricao);
				inicio1 = inicio1->prox;
			break;
		}
	}

	while (inicio2 != (*fim)->prox) {
		switch (tipoOrdena) {
			case T:
				insereNaLista(lAux, inicio2->prior, inicio2->chegada, inicio2->descricao);
				inicio2 = inicio1->prox;
			break;
			case P:
				insereNaLista(lAux, inicio2->prior, inicio2->chegada, inicio2->descricao);
				inicio2 = inicio2->prox;
			break;
		}
	}

	celula* afterFim = (*fim)->prox;
	destroiIntervalo(*inicio, *fim);

	*inicio = lAux->primeiro;
	*fim = lAux->ultimo;
	(*fim)->prox = afterFim;

	free(lAux);
}

void ordenaAux(celula** inicio, celula** fim, int n, int tipoOrdena) {
	if (inicio != fim && inicio != NULL) {
		celula* meio = encontraMeio(*inicio, *fim, n);
		int m = (n - 1)/2;
		ordenaAux(inicio, &meio, m, tipoOrdena);
		ordenaAux(&(meio->prox), fim, n - m, tipoOrdena);
		merge(inicio, &meio, fim, tipoOrdena);
		
	}
}*/

void divideLista(celula* c, celula** esquerda, celula** direita) {
	celula* fim;
	celula* meio;

	meio = c;
	fim = c->prox;

	while (fim != NULL) {
		fim = fim->prox;
		if (fim != NULL) {
			meio = meio->prox;
			fim = fim->prox;
		}
	}

	*esquerda = c;
	*direita = meio->prox;
	meio->prox = NULL;

}

celula* merge(celula* esquerda, celula* direita, int tipoOrdena) {

	celula* nova = NULL;

	if (!esquerda) return direita;
	if (!direita) return esquerda;

	switch (tipoOrdena) {
		case P:
			if (esquerda->prior > direita->prior) {
				nova = esquerda;
				nova->prox = merge(esquerda->prox, direita, tipoOrdena);
			}
			else {
				nova = direita;
				nova->prox = merge(esquerda, direita->prox, tipoOrdena);
			}
		break;
		case T:
			if (menorQueHorario(esquerda->chegada, direita->chegada)) {
				nova = esquerda;
				nova->prox = merge(esquerda->prox, direita, tipoOrdena);
			}
			else {
				nova = direita;
				nova->prox = merge(esquerda, direita->prox, tipoOrdena);
			}
		break;
	}
	return nova;
}

void printCelula(celula* c) {
	printf("%02d %02d:%02d:%02d %s\n", c->prior, c->chegada.hh, c->chegada.mm, c->chegada.ss, c->descricao);
}

void printAux(celula* c) {
	while (c != NULL) {
		printCelula(c);
		c = c->prox;
	}
	printf("\n");
}

void ordenaAux(celula** c, int tipoOrdena) {
	celula* esquerda;
	celula* direita;

	if (*c == NULL || (*c)->prox == NULL) return;
	divideLista(*c, &esquerda, &direita);

	ordenaAux(&esquerda, tipoOrdena);
	ordenaAux(&direita, tipoOrdena);
	*c = merge(esquerda, direita, tipoOrdena);
}


void ordenaLista(lista* l, int tipoOrdena) {
	if (l->tam != 0) ordenaAux(&(l->primeiro), tipoOrdena);
	
}

void printLista(lista* l, int tipoOrdena) {
	if (tipoOrdena != N)
	ordenaLista(l, tipoOrdena);

	celula* it = l->primeiro;
	while (it != NULL) {
		printCelula(it);
		it = it->prox;
	}
	printf("\n");
}

void encontraMaxPrior(lista *l, celula** anterior, celula** alvo) {
	celula* ant = NULL;
	celula* atual = l->primeiro;
	int maxPrior = -1;

	while (atual != NULL) {
		if (atual->prior > maxPrior) {
			maxPrior = atual->prior;
			*anterior = ant;
			*alvo = atual;
		}
		ant = atual;
		atual = atual->prox;
	}
}

void encontraMinHorario(lista* l, celula** anterior, celula** alvo) {
	celula* ant = NULL;
	celula* atual = l->primeiro;
	horario minHorario;
	minHorario.hh = 25;

	while (atual != NULL) {
		if (menorQueHorario(atual->chegada, minHorario)) {
			minHorario = atual->chegada;
			*anterior = ant;
			*alvo = atual;
		}
		ant = atual;
		atual = atual->prox;
	}
}

void printNext(lista* l, int tipoOrdena) {
	if (l != NULL && l->tam != 0) {
		celula* anterior;
		celula* alvo;
		switch (tipoOrdena) {
			case P:
				encontraMaxPrior(l, &anterior, &alvo);
			break;
			case T:
				encontraMinHorario(l, &anterior, &alvo);
			break;
		}
		printCelula(alvo);
		printf("\n");
	}
}