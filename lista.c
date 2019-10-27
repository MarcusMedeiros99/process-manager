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
	if (nova) insereAux(l, nova);
}

void destroiAux(celula* c) {
	if (c != NULL) {
		destroiAux(c->prox);
		free(c);
	}
}

void destroiLista(lista* l) {
	destroiAux(l->primeiro);
	free(l);
}


//Função que divide a lista iniciada em "c" em duas listas de tamanho igual.
//A listas são retornadas em "esquerda" e "direita". Dois ponteiros auxiliares
//são inicializados no começo da lista e ambos vão percorrendo em direção ao
//fim do vetor, mas um deles percorre dois nós de cada vez. Quando um desses
//ponteiros chega ao fim da lista, o outro está na metade, e a função termina
//colocando o último nó da lista da esquerda apontando para NULL.
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

//Função que retorna uma lista ordenada intercalando duas listas ordenadas
//A flag tipoOrdena indica se a ordenação ocorre por horário (T) ou prioridade (P)
celula* merge(celula* esquerda, celula* direita, int tipoOrdena) {

	celula* nova = NULL;

	if (!esquerda) return direita;
	if (!direita) return esquerda;

	switch (tipoOrdena) {
		case P: //Ordenação por prioridade
			if (esquerda->prior > direita->prior) {
				nova = esquerda;
				nova->prox = merge(esquerda->prox, direita, tipoOrdena);
			}
			else {
				nova = direita;
				nova->prox = merge(esquerda, direita->prox, tipoOrdena);
			}
		break;
		case T: //Ordenação por horário
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

//Função de ordenação da lista utilizando mergesort.
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

//Função auxiliar para imprimir uma celula da lista
void printCelula(celula* c) {
	printf("%02d %02d:%02d:%02d %s\n", c->prior, c->chegada.hh, c->chegada.mm, c->chegada.ss, c->descricao);
}

//Imprime a lista de acordo com a flag tipoOrdena. A flag tipoOrdena indica
//se a ordenação ocorre por horário (T) ou prioridade (P) ou se não há
//ordenação (N)
void printLista(lista* l, int tipoOrdena) {
	if (l) {
		if (tipoOrdena != N) ordenaLista(l, tipoOrdena);

		celula* it = l->primeiro;
		while (it != NULL) {
			printCelula(it);
			it = it->prox;
		}
		printf("\n");
	}
}

//Função que encontra elemento de maior prioridade na lista. Como a 
//lista é simplesmente encadeada, é útil guardar o elemento imediatamente
//anterior a fim de realizar remoções
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

//Função que encontra elemento de menor horário de chegada na lista. Como a 
//lista é simplesmente encadeada, é útil guardar o elemento imediatamente
//anterior a fim de realizar remoções
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

//Função que realiza impressão do elemento da lista de maior
//prioridade (tipoOrdena = P) ou de menor horário de chegada (tipoOrdena = T)
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